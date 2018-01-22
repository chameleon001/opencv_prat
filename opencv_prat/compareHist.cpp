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
//};
//
//class ImageComparator {
//private:
//    cv::Mat reference; // 원본
//    cv::Mat input; // 비교할 대상
//    cv::MatND refH;
//    cv::MatND inputH;
//
//    ColorHistogram hist;
//    int div;
//
//public:
//    ImageComparator() : div(32) { // div=32 초기화
//    }
//
//    // 신뢰할 수 있는 유사도 측정 방법을 얻으려면 컬러 개수를 반드시 감축해야 함
//    // 클래스에 컬러 감축 인자를 포함하며, 질의와 입력 영상에 모두 적용
//    void setColorReduction(int factor) {
//        // 컬러 감축 인자
//        // 각 차원별 인자에 의해 컬러 공간 감축 시킨 영상 비교
//        div = factor;
//    }
//
//    int getColorReduction() {
//        return div;
//    }
//
//    void setReferenceImage(const cv::Mat& image) {
//        // 질의 영상도 적절한 세터를 사용해 지정, 질의 영상에 대해 컬러를 감축
//        reference = hist.colorReduce(image, div);
//        refH = hist.getHistogram(reference);
//    }
//
//    double compare(const cv::Mat& image) {
//        // compare 메소드는 지정한 입력 영상과 참조 영상을 비교
//        // 두 영상이 얼마나 유사한지 알려주는 점수 반환
//        input = hist.colorReduce(image, div);
//        inputH = hist.getHistogram(input);
//
//        return cv::compareHist(refH, inputH, CV_COMP_INTERSECT);
//    }
//};
//
//int main()
//{
//
//    cv::Mat image = cv::imread("123.jpg"); // 참조 영상 읽기
//    cv::namedWindow("god do");
//    cv::imshow("god do", image); // 영상 띄워 보기
//     
//    ImageComparator c;
//    c.setReferenceImage(image);
//    // 이 클래스는 주어진 질의 영상과 유사한 영상을 검사하는 데 사용
//
//    cv::Mat input = cv::imread("salted.jpg");
//    cv::namedWindow("god_salted do");
//    cv::imshow("god_salted", input); // 영상 띄워 보기
//
//    std::cout << "god do vs god_salted: " << c.compare(input) << std::endl;
//    // 참조 영상과 비교 
//
//    cv::waitKey(0);
//
//    return 0;
//}
//
///*
//
//- 대부분 히스토그램 비교 측정은 빈도 간의 비교를 기반으로 함.
//- 히스토그램의 빈도를 비교할 때 이웃한 빈도를 사용하지 않는다.
//- 따라서 두 컬러 히스토그램의 유사도를 측정하기 전에 컬러 공간을 감축하는 것이 중요.
//
//- cv::compareHist를 호출하는 방법은 쉽다.
//- 두 히스토그램을 바로 입력하고 이 함수에서 측정된 거리를 반환한다.
//- 플래그를 사용하길 원하는 측정 방법을 지정한다.
//- ImageComparator 클래스에서 인터섹션 방법을 사용(CV_Comp_INTERSECT 플래그를 함께 사용)한다.
//- 이 방법은 간단하게 각 빈도, 즉 각 히스토그램 내의 두 개 값을 비교하고, 그 중 최솟값을 유지, 유사도 측정은 최소값의 합으로 간단해진다.
//- 이런 경우 모두 컬러가 전혀 없되 화소의 총 개수가 동일한 두 히스토그램을 갖는 두 영상의 인터섹션 값은 0이다.
//
//- 사용할 수 있는 다른 방법은 카이 제곱(CV_COMP_CHISQR 플래그)이며, 빈도 간 정규 제곱 차이의 합으로 구한다.
//- 카이 제곱 공식
//- 상관관계 방법(CV_COMP_CORREL 플래스)은 신호 처리에서 두 신호 간의 유사도를 측정하기 위해 사용하는 정규 상관관계수 연산자.
//- 바타챠르야 측정(CV_COMP_BHATTACHARYYA 플래스)은 두 확률 분포 간의 유사도를 측정하기 위한 통계로 사용.
//*/