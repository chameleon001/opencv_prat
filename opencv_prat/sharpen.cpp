////-라플라시안 연산자(선명한 연산자)
////- 영상에 라플라시간을 거친 결과를 빼면 영상 에지가 두드러지게 돼 선명한 영상이 됨.
////- sharpened_pixel = 5 * current - left - right - up - down;
////-current는 가운데, left는 바로 현재 한 행의 왼쪽의 화소, up은 이전 줄의 가운데에 대응 하는 화소이다.
////
////Example
//
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
//
//void sharpen(const cv::Mat &image, cv::Mat &result) {
//    result.create(image.size(), image.type());
//    // 필요하면 할당
//    // create는 원본의 사이즈와 타입을 똑같이 만들어줌
//
//    for (int j = 1; j<image.rows - 1; j++) { // 모든 행에 대해(처음과 마지막을 제외하고)
//        const uchar* previous = image.ptr<const uchar>(j - 1); // 이전 행
//        const uchar* current = image.ptr<const uchar>(j); // 현재 행
//        const uchar* next = image.ptr<const uchar>(j + 1); // 다음 행
//        uchar* output = result.ptr<uchar>(j); // 결과 행
//
//        for (int i = 1; i<image.cols - 1; i++) {
//            *output++ = cv::saturate_cast<uchar>(5 * current[i] + current[i - 1] - current[i + 1] - previous[i] - next[i]);
//            output[i] = cv::saturate_cast<uchar>(5 * current[i] - current[i - 1] - current[i + 1] - previous[i] - next[i]);
//        }
//    }
//    // 처리하지 않는 화소를 0으로 설정
//    result.row(0).setTo(cv::Scalar(0));
//    result.row(result.rows - 1).setTo(cv::Scalar(0));
//    result.col(0).setTo(cv::Scalar(0));
//    result.col(result.cols - 1).setTo(cv::Scalar(0));
//}
//
///*
//- 이웃 화소에 대한 계산이 끝나면 대부분 커널 행렬을 표시.
//- 다음 예제에서 사용한 선명한 필터에서 커널은 다음과 같다.
//0  -1  0
//-1  5  -1
//0  -1  0
//
//- 따로 명시되지 않으면 현재 화소는 커널의 중심에 대응.
//- 커널 내 각 셀에 있는 값은 일치하는 화소와 곱하는 인자를 의미.
//- 화소에 대한 커널을 적용한 결과는 모든 곱셈의 합. 커널의 크기는 이웃 크기에 대응.
//- 선명화 필터에서 볼 수 있듯 현재 화소의 네 가지 수평과 수직 이웃은 -1로 곱하는데, 가운데는 5를 곱한다.
//
//- 필터링은 영상처리에서 일반적인 작업이므로, OpenCV는 cv::filter2D함수로 해당 작업을 수행한다. - 선명화 함수 (사용하기 위해서는 커널 - 행렬 형태로 정의해야 함)
//*/
//void sharpen2D(const cv::Mat &image, cv::Mat &result) {
//    cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
//    // 커널 생성(모든 값을 0으로 초기화)
//    kernel.at<float>(1, 1) = 5.0; // 커널 값에 할당
//    kernel.at<float>(0, 1) = -1.0;
//    kernel.at<float>(2, 1) = -1.0;
//    kernel.at<float>(1, 0) = -1.0;
//    kernel.at<float>(1, 2) = -1.0;
//
//    cv::filter2D(image, result, image.depth(), kernel);
//    // 영상 필터링
//}
//
//void color_sharpen2D(const cv::Mat &image, cv::Mat &result) {
//    cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0, 0, 0));
//    // 커널 생성(모든 값을 0으로 초기화)
//    kernel.at<float>(1, 1) = 5.0;// 커널 값에 할당
//    kernel.at<float>(0, 1) = -1.0;
//    kernel.at<float>(2, 1) = -1.0;
//    kernel.at<float>(1, 0) = -1.0;
//    kernel.at<float>(1, 2) = -1.0;
//
//    cv::filter2D(image, result, image.depth(), kernel);
//    // 영상 필터링
//}
//
//
//
//int main()
//{
//    //cv::Mat image = cv::imread("123.jpg", 0);
//    //cv::Mat result;
//
//    //sharpen(image, result);
//
//    //cv::namedWindow("Image");
//    //cv::imshow("Image", image);
//
//    //cv::namedWindow("Result");
//    //cv::imshow("Result", result);
//
//    ////cv::waitKey(5000);
//
//    //
//    //cv::Mat image1 = cv::imread("123.jpg", 0);
//    //cv::Mat result1;
//
//
//    //sharpen2D(image1, result1);
//
//    //cv::namedWindow("Image a bc");
//    //cv::imshow("Image abc", image1);
//
//    //cv::namedWindow("Result abc");
//    //cv::imshow("Result abc", result1);
//
//    ////cv::waitKey(5000);
//
//    cv::Mat image2 = cv::imread("123.jpg"); // imread 뒤에 0안붙이면 컬러
//    cv::Mat result2;
//
//
//    color_sharpen2D(image2, result2);
//
//    cv::namedWindow("Image ccc");
//    cv::imshow("Image ccc", image2);
//
//    cv::namedWindow("Result ccc");
//    cv::imshow("Result ccdc", result2);
//
//    cv::waitKey(50000);
//
//
//
//    return 0;
//}
////
////
////
////
////예제 분석
////
////- 이전 행과 다음 행의 이웃 화소에 접근하려면 다른 하나에 대해서 간단히 포인터를 추가해 정의하며 서로 결합해 증가한다.
////- cv::staturate_cast는 0이하 255미만이라는 화소값 허용 범위를 벗어나는 경우가 종종 있다.
////- cv::staturate_cast<uchar>함수를 이용해서 음수 값을 0으로, 255 이상 값을 255로 변환한다.
////
////- 이웃을 완전히 정의하지 않았기 때문에 테두리 화소를 처리할 수 없어서 별도로 다뤄야하며, 여기서는 0으로 설정한다.
////- row와 col 메소드를 사용해 테두리 화소를 0으로 설정.
////- setTo : 모든 행렬 요소에 대한 값을 할당.
////- result.row(0).setTo(cv::Scalar(0)); // 영상의 첫 번째 행에 있는 모든 화소에 0을 할당
////-3채널 컬러 영상이면 각 채널 화소에 할당하는 세 가지 값을 지정하는 cv::Scalar(a, b, c) 사용.