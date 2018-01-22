//#include <iostream>
//#include <vector>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/video/tracking.hpp>
//#include <opencv2/video/video.hpp>
//
//class ColorHistogram {
//private:
//    int histSize[3];
//    float hranges[2];
//    const float* ranges[3];
//    int channels[3];
//public:
//    ColorHistogram() {
//        // 컬러 히스토그램을 위한 인자 준비
//        histSize[0] = histSize[1] = histSize[2] = 256;
//        hranges[0] = 0.0;    // BRG 범위
//        hranges[1] = 255.0;
//        ranges[0] = hranges; // 모든 채널은 같은 범위를 가짐 
//        ranges[1] = hranges;
//        ranges[2] = hranges;
//        channels[0] = 0;  // 세 가지 채널 
//        channels[1] = 1;
//        channels[2] = 2;
//    }
//
//    // 마스크와 함께 1차원 색상 히스토그램 계산
//    // BGR 원시 영상은 HSV로 변환
//    // 낮은 채도를 갖는 화소를 무시
//    cv::MatND getHueHistogram(const cv::Mat &image, int minSaturation = 0) {
//        cv::MatND hist;
//        cv::Mat hsv; // HSV 컬러 공간 변환
//        cv::cvtColor(image, hsv, CV_BGR2HSV); // HSV 공간으로 변환
//        cv::Mat mask; // 사용하는 마스크 (또는 사용하지 않음)
//
//        if (minSaturation > 0) {
//            std::vector<cv::Mat> v; // 3채널을 3개 영상으로 분리
//            cv::split(hsv, v); // 영상 분리
//            cv::threshold(v[1], mask, minSaturation, 255, cv::THRESH_BINARY);
//            // 낮은 채도 화소를 마스크로 제외
//        }
//
//        // 1차원 색상 히스토그램 인자 준비
//        hranges[0] = 0.0;
//        hranges[1] = 180.0;
//        channels[0] = 0; // 색상 채널
//        cv::calcHist(&hsv, // 히스토그램 계산 
//            1,   // 단일 영상의 히스토그램만
//            channels, // 대상 채널               
//            cv::Mat(), // 마스크 프로그램         
//            hist,  // 결과 히스토그램         
//            1,   // 1D 히스토그램           
//            histSize, // 빈도수                  
//            ranges  // 화소값 범위             
//            );
//        return hist;
//    }
//};
//
//// 히스토그램 역투영 알고리즘에서 컬러 정보를 사용할 수 있는 방법
//// 먼저 역투영 처리 과정을 캡슐화한 클래스를 정의
//// 필요한 속성과 초기 데이터를 정의
//class ContentFinder {
//private:
//    float hranges[2];
//    const float* ranges[3];
//    int channels[3];
//    float threshold;
//    cv::MatND histogram;
//public:
//    ContentFinder() : threshold(-1.0f) {
//        ranges[0] = hranges; // 모든 채널은 동일한 범위를 가짐
//        ranges[1] = hranges;
//        ranges[2] = hranges;
//    }
//
//    // 감지 결과를 보여주기 위한 이진 맵을 생성할 때 사용하는 경계값 파라미터를 정의
//    // 파라미터를 음수 값으로 설정하면 원시 확률 맵을 반환
//    void setThreshold(float t) {
//        // 히스토그램 값인 [0,1]에서 경계값 설정
//        threshold = t;
//    }
//
//    float getThreshold() {
//        // 경계값 가져오기
//        return threshold;
//    }
//
//    // 입력 히스토그램은 반드시 정규화 되어야 함
//    void setHistogram(const cv::MatND& h) {
//        // 참조 히스토그램 설정
//        histogram = h;
//        cv::normalize(histogram, histogram, 1.0);
//    }
//
//    cv::Mat find(const cv::Mat& image) {
//        // 히스토그램에 속하는 화소 찾기
//        cv::Mat result;
//
//        hranges[0] = 0.0; // [0,255] 범위
//        hranges[1] = 255.0;
//        channels[0] = 0;  // 세 가지 채널 
//        channels[1] = 1;
//        channels[2] = 2;
//
//        cv::calcBackProject(&image, // 입력 영상
//            1,            // 이 때 한 영상만 사용
//            channels,     // 영상 채널에 속하는 히스토그램 차원인 벡터 지정            
//            histogram,   // 히스토그램 사용                                           
//            result,       // 역투영 영상 결과                                          
//            ranges,       // 각 차원에 대한 값 범위                                    
//            255.0         // 히스토그램을 1을 255로 매핑하기 위해 선택한 스케일링 인자 
//            );
//
//        if (threshold>0.0) {
//            // 이진 영상을 얻기 위한 역투영 경계값
//            cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
//        }
//
//        return result;
//    }
//
//    // 히스토그램을 역투영하려면 영상과 범위(모든 채널은 여기서 동일한 범위를 갖는다고 가정),
//    // 사용하는 채널 목록을 간단하게 지정할 필요가 있다.
//    cv::Mat find(const cv::Mat& image, float minValue, float maxValue, int *channels, int dim) {
//
//        cv::Mat result;
//
//        hranges[0] = minValue;
//        hranges[1] = maxValue;
//
//        for (int i = 0; i<dim; i++)
//            this->channels[i] = channels[i];
//
//        cv::calcBackProject(&image, // 입력 영상
//            1,            // 이 때 한 영상만 사용
//            channels,     // 영상 채널에 속하는 히스토그램 차원인 벡터 지정            
//            histogram,   // 히스토그램 사용                                           
//            result,       // 역투영 영상 결과                                          
//            ranges,       // 각 차원에 대한 값 범위                                    
//            255.0         // 히스토그램을 1을 255로 매핑하기 위해 선택한 스케일링 인자 
//            );
//
//        if (threshold>0.0) {
//            //이진 영상을 얻기 위한 역투영 경계값
//            cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
//        }
//        return result;
//    }
//};
//
//int main()
//{
//    cv::Mat image = cv::imread("move.jpg");
//    // 참조 영상 읽기
//    //cv::Mat imageROI = image(cv::Rect(110, 260, 35, 40));
//    // 원숭이 얼굴 ROI
//    cv::Mat imageROI = image(cv::Rect(100, 95, 85, 82));
//    cv::namedWindow("Image1");
//    cv::imshow("Image1", image);
//
//    int minSat = 65;
//    ColorHistogram hc; // 색상 히스토그램 가져오기
//    cv::MatND colorhist = hc.getHueHistogram(imageROI, minSat);
//
//    ContentFinder finder;
//    finder.setHistogram(colorhist);
//    // 결과 히스토그램을 입력으로 ContentFinder 클래스 인스턴스에 넣음
//    finder.setThreshold(0.2f);
//
//    // HSV 공간으로 변환
//    cv::Mat hsv;
//    cv::cvtColor(image, hsv, CV_BGR2HSV);
//
//    std::vector<cv::Mat> v; // 3채널을 3개 영상으로 분리
//    cv::split(hsv, v); // 영상 분리
//
//    cv::threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
//    // 낮은 채도를 갖는 화소 제거
//    cv::namedWindow("Saturation");
//    cv::imshow("Saturation", v[1]);
//
//    int ch[1] = { 0 };
//    cv::Mat result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//    // 색상 히스토그램의 역투영 가져오기
//    cv::namedWindow("Result Hue");
//    cv::imshow("Result Hue", result);
//
//    cv::bitwise_and(result, v[1], result);
//    cv::namedWindow("Result Hue and");
//    cv::imshow("Result Hue and", result);
//
////    cv::rectangle(image, cv::Rect(110, 260, 35, 40), cv::Scalar(0, 0, 255));
//
//    cv::rectangle(image, cv::Rect(100, 95, 85, 82), cv::Scalar(0, 0, 255));
//
//    cv::namedWindow("Image 1 result");
//    cv::imshow("Image 1 result", image);
//   //cv::rectangle(image, cv::Rect(110, 260, 35, 40), cv::Scalar(0, 255, 0));
//    cv::rectangle(image, cv::Rect(100, 95, 85, 82), cv::Scalar(0, 255, 0));
//
//    image = cv::imread("move2.jpg");
//    // 새로운 원숭이 얼굴의 위치를 찾기 원하는 두 번째 영상 읽기
//    // 이번 영상도 HSV 공간으로 변환해야 함
//    cv::namedWindow("Image2");
//    cv::imshow("Image2", image);
//
//    cv::cvtColor(image, hsv, CV_BGR2HSV); // HSV 공간으로 변환
//    cv::split(hsv, v); // 영상 분리
//    cv::threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
//    // 낮은 채도 화소를 마스크로 제외
//    // cv::namedWindow("Saturation");
//    // cv::imshow("Saturation",v[1]);
//
//    result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//    // 색상 히스토그램의 역투영 가져오기
//    // cv::namedWindow("Result Hue");
//    // cv::imshow("Result Hue",result);
//
//    cv::bitwise_and(result, v[1], result);
//    // 낮은 채도 화소 제거 (일정 채도 화소 이하 제거)
//    // cv::namedWindow("Result Hue and");
//    // cv::imshow("Result Hue and",result);
//
//    // 색상 히스토그램의 역투영 가져오기
//    finder.setThreshold(-1.0f);
//    result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//    cv::bitwise_and(result, v[1], result);
//    // cv::namedWindow("Result Hue and raw");
//    // cv::imshow("Result Hue and raw",result);
//
//    // 초기 직사각형 영역 (초기 영상 내 원숭이 얼굴 위치)에서
//    // cv::meanShift 알고리즘이 새로운 원숭이 얼굴 위치에 대한 rect 객체를 갱신
//   // cv::Rect rect(110, 260, 35, 40);
//    cv::Rect rect(100, 95, 85, 82);
//    cv::rectangle(image, rect, cv::Scalar(0, 0, 255));
//    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER, 10, 0.01);
//    cv::meanShift(result, rect, criteria);
//    // <opencv2/video/tracking.hpp> 필요
//    cv::rectangle(image, rect, cv::Scalar(0, 255, 0));
//
//    cv::namedWindow("Image 2 result");
//    cv::imshow("Image 2 result", image);
//
//    cv::waitKey(0);
//
//    return 0;
//}
//
//
///*
//
//
//예제 분석
//
//- 객체를 특성화하기 위한 HSV 컬러 공간의 색상 컴포넌트를 사용 (따라서 영상은 처음에 변환해야 됨)
//- 색상 컴포넌트는 CV_BGR2HSV 플래그를 사용한 결과 영상의 첫 번째 채널.
//- 8비트 컴포넌트로서 색상 값은 0부터 180(cv::cvtColor와 함께 원시 영상과 동일한 타입을 갖는 변환된 영상)까지 있다.
//- 색상 영상을 추출하려면 cv::split 함수를 이용해 3채널 HSV 영상을 분리해 세 가지 1채널 영상을 넣음.
//- 세 가지 영상을 std::vector 인스턴스에 넣으면 색상 영상은 벡터의 첫 번째(즉, 첨자는 0) 항목이 됨.
//
//- 컬러의 색상 요소를 사용하면 채도를 취해 저장 (벡터의 두 번째 항목)하는 것이 중요.
//- 컬러의 채도가 낮으면 색상 정보는 불안정하고 신뢰가 없어짐.
//- 사실상 낮은 채도 컬러이기 때문에 B, G, R 컴포넌트는 거의 같고, 정확한 컬러 재현을 조사하는 데 어려움을 겪게 됨.
//- 즉, 결과적으로 낮은 채도를 갖는 컬러의 색상 요소를 무시함.
//- 히스토그램(minSat 파라미터로 getHueHistogram 메소드에서 이 경계값 밑인 채도를 갖는 화소를 마스크로 제거)에서 계산하지 않고 역투영 결과(cv::meanShift를 호출하기 전에 낮은 채도 컬러를 갖는 화소에 모두 반응하는 감지 부분을 제거하는 cv::bitwise_and 연산자를 사용)에서 제거.
//
//- 평균 이동 알고리즘은 확률 함수의 지역 최대치인 위치를 찾도록 반복적으로 실행.
//- 미리 지정한 창 내부의 데이터 점인 중심점이나 가중 평균을 찾는 방식으로 수행.
//- 이 알고리즘은 다음 중심 위치로 창을 이동하고, 창 내부의 중심인 안정적인 점으로 수렴할 때까지 과정을 반복.
//
//- OpenCV는 두 가지의 중지 기준을 정의해 구현
//- 각기 반복 최대 횟수의 창 중심 간의 위치 변화량 이하로서, 위치는 안정적인 점으로 수렴하도록 고려.
//- 두 가지 기준은 cv::TermCriteria 인스턴스에 저장.
//- cv::meanShift 함수는 수행 횟수를 반환
//*/