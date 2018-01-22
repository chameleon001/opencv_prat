//
//오버로드된 영상 연산자
//
//- 대부분 산술 함수는 해당 연산자를 오버로드 하기 때문에 cv::addWeighted를 호출하려면 다음 코드와 쓸 수 있다.
//- result = 0.7*image1 + 0.9*image2; (가중 합을 쓰는 두 가지 방법은 동일)
//- cv::saturate_cast 함수를 양쪽 경우에도 여전히 호출한다.
//
//- C++ 연산자 오버로드 : 비트 연산자 &, | , ^, ~, min, max, abs 함수.비교 연산자 <, <= , == , != , >=
//    -행렬 곱 m1*m2(m1과 m2 모두 cv : Mat 인스턴스), 역행렬 m1.inv(), 전치행렬 m1.t(), 행렬식 m1.determinant(), 벡터 놈 v1.norm(), 외적 v1.aross(v2), 내적 v1.dot(v2)
//
//    - 영상 화소를 조회하는 반복문을 사용한 컬러 감축 함수를 여기서 입력 영상에 대한 산술 연산을 사용해 함수를 간단히 다시 쓸 수 있다.
//    - image = (image&cv::Scalar(mask, mask, mask)) + cv::Scalar(div / 2, div / 2, div / 2);
//
//-cv::Scalar는 컬러 영상을 다루기 때문에 사용.
//- And와 스칼라 합(영상 반복문 내부 전체 작업을 수행하는 대신)을 호출함으로 써 코드가 매우 단순해진다.
//
//- 소스

//
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//void colorReduce(cv::Mat &image, int div = 64) {
//    int nl = image.rows;
//    int nc = image.cols*image.channels();
//    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//    // 화소값을 반올림하기 위해 사용하는 마스크
//    uchar mask = 0xFF << n; // 예, div=16이면 mask= 0xF0
//
//    image = (image&cv::Scalar(mask, mask, mask)) + cv::Scalar(div / 2, div / 2, div / 2);
//    // 영상 화소를 조회하는 반복문을 사용한 컬러 감축 함수를 다음과 같이 간단히 쓸 수 있다.
//}
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//    cv::Mat background = cv::imread("456.jpg");
//    cv::Mat result;
//
//    result = 0.8*image + 0.4*background; // 연산자 오버로드
//
//    cv::namedWindow("Result");
//    cv::imshow("Result", result);
//
//    colorReduce(image); // 컬러 감축 함수 호출
//
//    cv::namedWindow("Result2");
//    cv::imshow("Result2", image);
//
//    cv::waitKey(0);
//
//    return 0;
//}

//-결과
//
//영상 채널 분리
//
//- 영상의 각 채널을 독립적으로 처리할 수 있다.
//- 이는 영상 조회 반복문에서 얻을 수 있다.
//- 컬러 영상의 세 가지 채널을 세 가지의 서로 다른 cv : Mat 인스턴스에 복사하는 cv::split 함수를 사용할 수 있다.
//
//- 소스
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <vector>
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//    cv::Mat background = cv::imread("456.jpg", 0); // 독립적 처리 (그레이레벨 영상이어야 함)
//    cv::Mat result;
//
//    std::vector<cv::Mat> planes; // 3개 영상의 백터 생성
//    cv::split(image, planes); // 3채널 단일 영상을 각 1채널 영상으로 분리
//    planes[2] += background; // 파랑 채널 합치기
//                             // planes[1]이면 초록 채널 합치기
//                             // planes[2]이면 빨강 채널 합치기
//    cv::merge(planes, result); // 3개의 1채널을 3채널을 갖는 단일 영상으로 통합
//
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//
//    cv::namedWindow("Background");
//    cv::imshow("Background", background);
//
//    cv::namedWindow("Result");
//    cv::imshow("Result", result);
//
//    cv::waitKey(0);
//
//    return 0;
//}
