//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//void colorReduce(cv::Mat &image, int div = 64) {
//    // 밑줄은 템플릿 메소드.
//    // 반복자는 cv::MaIterator_<cv::Vec3b> it; 또는,
//    // cv::Mat_<cv::Vec3b>::iterator it; 으로 선언.
//    // 반복자는 반환 타입이 명시되어야 한다.
//    // 컬러 감축을 처리하기 때문에 cv:Vec3b를 반환.
//    cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
//    // 초기 위치에서 반복자 얻기
//    cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
//    // 마지막 위치에서 얻기
//
//    for (; it != itend; ++it) { // 모든 화소를 조회
//                                // 각 화소에 대한 처리
//        (*it)[0] = (*it)[0] / div*div + div / 2; // 포인터 형태 캐스팅
//        (*it)[1] = (*it)[1] / div*div + div / 2;
//        (*it)[2] = (*it)[2] / div*div + div / 2;
//        // 각 화소 처리 끝
//    }
//}
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//
//    colorReduce(image);
//
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//    cv::waitKey(5000);
//
//    return 0;
//}