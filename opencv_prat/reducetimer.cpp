//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//void colorReduce(cv::Mat &image, int div = 64) {
//
//    int nl = image.rows; // 행 개수
//    int nc = image.cols; // 열 개수
//
//    for (int j = 0; j<nl; j++) {
//        for (int i = 0; i<nc; i++) {
//            // 각 화소에 대한 처리
//            image.at<cv::Vec3b>(j, i)[0] = image.at<cv::Vec3b>(j, i)[0] / div*div + div / 2;
//            image.at<cv::Vec3b>(j, i)[1] = image.at<cv::Vec3b>(j, i)[1] / div*div + div / 2;
//            image.at<cv::Vec3b>(j, i)[2] = image.at<cv::Vec3b>(j, i)[2] / div*div + div / 2;
//            // 각 화소 처리 끝 ----------------
//        } // 행 끝                   
//    }
//}
//
//
////컬러 감축 공식.
//void color_colorReduce(cv::Mat &image, int div = 64) {
//
//    int nl = image.rows; // 행 개수
//    int nc = image.cols; // 열 개수
//
//    if (image.isContinuous()) { // 연속된 영상인가.
//        nc = nc * nl; // 채울 화소가 없다면...
//        nl = 1; // 지금은 1차원 배열
//    }
//
//    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//    // 화소값을 반올림할 때 사용하는 마스크
//    uchar mask = 0xFF << n; // 예를 들어 div=16, mask=0xF0 
//
//    for (int j = 0; j<nl; j++) { // 모든 화소를 대상으로
//        uchar* data = image.ptr<uchar>(j);
//        for (int i = 0; i<nc; i++) {
//            // 각 화소에 대한 처리
//            *data++ = *data&mask + div / 2;
//            *data++ = *data&mask + div / 2;
//            *data++ = *data&mask + div / 2;
//            // 각 화소 처리 끝 ----------------
//        } // 행 끝                   
//    }
//}
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//
//    double duration;
//    // 함수나 코드의 실행시간을 측정하는데 cv::getTickCount() 사용
//    duration = static_cast<double>(cv::getTickCount());
//    // cv::getTickCount() : 컴퓨터를 시작한 후부터 마지막 시간에 발생하는 클록 사이틀 수
//    std::cout << "duration : " << duration << std::endl;
//
//    colorReduce(image);
//
//    duration = static_cast<double>(cv::getTickCount()) - duration;
//    std::cout << "getTickCount()-duration : " << duration << std::endl;
//    duration /= cv::getTickFrequency();
//    std::cout << "getTickFrequency() : " << duration << std::endl;
//    // cv::getTickFrequency() : 밀리초 단위로 코드 부분의 실행시간 알아냄
//    // ms 단위인 경과 시간
//
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//    cv::waitKey(5000);
//
//    color_colorReduce(image);
//    cv::namedWindow("Image reduce");
//    cv::imshow("Image reduce", image);
//    cv::waitKey(5000);
//    return 0;
//}
//
