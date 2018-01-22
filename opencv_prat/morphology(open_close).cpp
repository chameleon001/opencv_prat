/*
-열림과 닫힘 연산자.
- 고수준 형태학 필터를 적용하려면 cv::morphologyEx 함수를 사용해야 함.
Example
*/
//
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//int main()
//{
//    cv::Mat image = cv::imread("gray.jpg");
//    // 입력 영상 읽기
//
//    cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
//    // 필터 효과를 더 두드러지게 5x5 구조 요소를 사용
//
//    // 닫기 연산자 적용
//    cv::Mat closed;
//    cv::morphologyEx(image, closed, cv::MORPH_CLOSE, element5);
//    cv::namedWindow("Closed Image");
//    cv::imshow("Closed Image", closed);
//
//    // 열림 연산자 적용
//    cv::Mat opened;
//    cv::morphologyEx(image, opened, cv::MORPH_OPEN, element5);
//    cv::namedWindow("Opened Image");
//    cv::imshow("Opened Image", opened);
//
//    cv::waitKey(0);
//
//    return 0;
//}


/*

- 열기와 닫힘 필터는 기본 침식과 팽창 연산 관점에서 간단히 정의 한다.
- 닫힘은 침식한 영상의 팽창으로 정의한다.
- 열림은 팽창한 영상의 침식으로 정의한다.
- 즉, 다음과 같이 호출해 영상의 침식을 계산할 수 있다.
*/
//
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//int main()
//{
//    cv::Mat image = cv::imread("gray.jpg");
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//
//    // 닫힘 필터 (영상의 침식 계산)
//    cv::Mat result;
//    cv::dilate(image, result, cv::Mat()); // 원 영상을 팽창
//    cv::erode(result, result, cv::Mat()); // 팽창된 영상에 대한 침식
//    cv::namedWindow("Closed Filter");
//    cv::imshow("Closed Filter", result);
//
//    // 열림 필터 (영상의 팽창 계산)
//    cv::Mat result2;
//    cv::erode(image, result2, cv::Mat()); // 원 영상을 침식
//    cv::dilate(result2, result2, cv::Mat()); // 침식된 영상에 대한 팽창
//    cv::namedWindow("Opened Filter");
//    cv::imshow("Opened Filter", result2);
//
//    cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
//    // 필터 효과를 더 두드러지게 5x5 구조 요소를 사용
//
//    // 영상 닫힘과 영상 열림
//    cv::morphologyEx(image, image, cv::MORPH_CLOSE, element5);
//    cv::morphologyEx(image, image, cv::MORPH_OPEN, element5);
//    cv::namedWindow("Closed and Opened Image");
//    cv::imshow("Closed and Opened Image", image);
//
//    cv::waitKey(0);
//
//    return 0;
//}

/*Result


- 닫힘 필터 : 하얀색 전경 객체의 작은 구멍이 채워졌음을 볼 수 있고, 인접한 여러 객체와 함께 연결됬다.구조 요소를 포함하기엔 매우 작은 임의의 홀이나 간격을 제거한다.
- 열림 필터 : 장면 내의 여러 작은 객체를 제거한다.구조 요소를 포함하기에 매우 작은 것을 모두 제거한다.

- 두 필터는 객체 감지에 자주 사용.
- 열림 필터가 영상 잡음으로 인한 작은 덩어리를 제거.
- 닫힘 필터가 잘못된 조각인 객체를 작은 부분으로 함께 연결. (즉, 순서대로 두 필터를 사용하는 것이 유리)
- 예제의 이진 영상을 순서대로 닫고 열면 Closed and Opened Image의 결과 처럼 장면 내의 주요 객체만 있는 영상을 얻는다.

- 해당 영상에 같은 열림 또는 닫힘 연산자를 여러 번 적용해도 아무런 효과가 없다.
- 첫 번째 열림에 의해 구멍이 채워졌다면 동일 한 필터를 추가로 적용해도 해당 영상에 아무런 변화를 주지 않는다.
- 이런 연산자를 수학 용어로 연산자가 멱등이 된다고 한다.f(x) = f(f(x))
*/