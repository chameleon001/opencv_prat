//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
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
//    // 히스토그램 계산.
//    cv::MatND getHistogram(const cv::Mat &image) {
//
//        cv::MatND hist;
//
//        // BGR 컬러 히스토그램
//        hranges[0] = 0.0;    // BRG 범위
//        hranges[1] = 255.0;
//        channels[0] = 0;  // 세 가지 채널
//        channels[1] = 1;
//        channels[2] = 2;
//
//        // 히스토그램 계산
//        cv::calcHist(&image,
//            1,   // 단일 영상의 히스토그램만
//            channels, // 대상 채널
//            cv::Mat(), //마스크 사용하지 않음
//            hist,  // 결과 히스토그램
//            3,   // 3D 히스토그램
//            histSize, // 빈도수
//            ranges  // 화소값 범위
//            );
//
//        return hist;
//    }
//
//    // 히스토그램 계산.
//    cv::SparseMat getSparseHistogram(const cv::Mat &image) {
//
//        cv::SparseMat hist(3, histSize, CV_32F);
//
//        // BGR 컬러 히스토그램
//        hranges[0] = 0.0;    // BRG 범위
//        hranges[1] = 255.0;
//        channels[0] = 0;  // 세 가지 채널 
//        channels[1] = 1;
//        channels[2] = 2;
//
//        // Compute histogram
//        cv::calcHist(&image,
//            1,   // 단일 영상의 히스토그램만
//            channels, // 대상 채널
//            cv::Mat(), // 마스크 사용하지 않음      
//            hist,  // 결과 히스토그램   
//            3,   // 3D 히스토그램          
//            histSize, // 빈도수                 
//            ranges  // 화소값 범위            
//            );
//
//        return hist;
//    }
//
//    cv::Mat colorReduce(const cv::Mat &image, int div = 64) {
//
//        int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//        // 화소값 반올림 하기 위해 사용하는 마스크
//        uchar mask = 0xFF << n; // 예, div=16이면 mask= 0xF0
//
//        cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
//        cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
//
//        // 결과 영상 설정(항상 1-채널)
//        cv::Mat result(image.rows, image.cols, image.type());
//        cv::Mat_<cv::Vec3b>::iterator itr = result.begin<cv::Vec3b>();
//
//        for (; it != itend; ++it, ++itr) {
//
//            (*itr)[0] = ((*it)[0] & mask) + div / 2;
//            (*itr)[1] = ((*it)[1] & mask) + div / 2;
//            (*itr)[2] = ((*it)[2] & mask) + div / 2;
//        }
//
//        return result;
//    }
//
//}; // 히스토그램 역투영 알고리즘에서 컬러 정보를 사용할 수 있는 방법
//   // 먼저 역투영 처리 과정을 캡슐화한 클래스를 정의
//   // 필요한 속성과 초기 데이터를 정의
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
//    cv::Mat color = cv::imread("123.jpg");
//
//    if (!color.data)
//        return 0;
//
//    cv::namedWindow("Image");
//    cv::imshow("Image", color);
//
//    ColorHistogram hc;
//    color = hc.colorReduce(color, 32);
//    cv::namedWindow("Color Image");
//    cv::imshow("Color Image", color);
//
//    cv::Mat imageROI = color(cv::Rect(0, 0, 165, 75)); // 파란 하늘 영역
//    //image 의 관심영역(ROI를 설정)
//    //하늘 사진이없어 강아지사진 그대로 사용..
//    cv::MatND hist = hc.getHistogram(imageROI);
//    ContentFinder finder;
//    finder.setHistogram(hist);
//    finder.setThreshold(0.05f);
//    cv::Mat result = finder.find(color);
//    // 히스토그램을 계산하고 영상의 하늘 일부를 감지하기 위한 find 메소드 사용
//  //  cv::imwrite("gray.jpg", result);
//    cv::namedWindow("Color Backproject Result");
//    cv::imshow("Color Backproject Result", result);
//  
//    cv::waitKey(0);
//
//    return 0;
//}