/*
침식과 팽창

-#5 : 가장 중요한 형태학적 연산자를 제시.
- 영상 형태학으로 수행하는 알고리즘을 이용한 영상 분할의 문제점 확인.

- 형태학 필터링 : 이산 영상 분석과 처리를 위해 나온 이론.
- 미리 정의된 모양 요소와 함께 면밀하게 조사해 영상을 변환시키는 연산자들의 모음.
- 모양 요소는 연산 결과를 결정하는 화소 주변을 교집합 한다.

- 침식과 팽창은 가장 기본적인 형태학 연산자.
- 수학적 형태학의 기본 도구는 구조 요소.
- 방향이 정의된(또한 고정점으로 불림) 구조 요소는 단순히 화소(모양)의 구성으로 정의 된다.
- 형태학 필터를 적용할 때 구조 요소를 사용해 영상 내의 각 화소를 면밀하게 조사하는 과정으로 구성 됨.
- 구조 요소의 기점이 주어진 화소로 정렬됬을 때 영상 간의 교집합은 특정 형태학이 적용된 화소 집합으로 정의 함.
- 원칙적으로 구조 요소는 임의의 모양일 수 있지만, 대부분 사각형 같은 간단한 모양, 원형, 또는 가운데가 시작점인 다이아몬드를 사용한다(효율적인 이유로).

- 형태학 필터는 일반적으로 이진 영상에 사용(#4의 첫 번째 예제에서 경계값으로 만든 이진 영상을 사용)
- 형태학에서는 높은(흰색) 화소값은 전경 객체로, 낮은(검은색) 화소값은 배경으로 규정하는데 여기서는 영상을 반전했음.
- 형태학 용어로 다음과 같은 영상을 #4에서 만든 영상의 보수(complement)라고 함.

- 침식과 팽창은 cv::erode와 cv::dilate로 구현한다.

Example
*/
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//int main()
//{
//    cv::Mat image = cv::imread("gray.jpg");
//    // 입력 영상 읽기
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//
//    // 영상 침식
//    cv::Mat eroded; // 목적 영상
//    cv::erode(image, eroded, cv::Mat());
//    cv::namedWindow("Eroded Image"); // 침식된 영상을 띄워봄
//    cv::imshow("Eroded Image", eroded);
//
//    // 영상 팽창
//    cv::Mat dilated; // 목적 영상
//    cv::dilate(image, dilated, cv::Mat());
//    cv::namedWindow("Dilated Image"); // 팽창된 영상을 띄워봄
//    cv::imshow("Dilated Image", dilated);
//
//    cv::waitKey(0);
//
//    return 0;
//}
/*
Result


예제 분석

- 위에서 두 필터는 각 화소 주변의 화소 집합(또는 이웃)에서 정의된 구조 요소로 연산한다.
- 현재 집합 내의 화소 위치와 함께 구조 요소의 고정점이 정렬됬으며, 구조 요소와 교집합 후의 모든 화소를 포함한다.

- 침식 : 정의한 화소 집합에서 찾은 최소 화소값을 현재 화소로 대치.
- 팽창 : 보수 연산자로, 정의한 화소 집합에서 찾은 최대 화소값을 현재 화소로 교체.
- 입력 이진 영상 : 오직 검은색(0)과 흰색(255) 화소를 포함하므로, 각 화소는 흰색이나 검은 화소 중 하나로 교체.

- 두 연산자의 효과를 체감할 수 있는 좋은 방법은 배경(검은색)과 전경(하얀색) 객체에 대해 생각하는 것.
- 침식 : 구조 요소가 화소 위치에서 배경(즉, 교차하는 집합의 화소 하나가 검은색)을 건드렸을 때 바꿔버린다면 화소를 배경으로 보내버린다. (객체의 크기가 감소됬기 때문에 침식, 매우 작은 객체 - '잡음' 의 일부도 완전히 제거 됨)
- 팽창 : 배경 화소로 구성된 구조 요소가 전경 객체를 건드리면 이 화소에 흰색 값을 할당. (객체의 크기는 커지며, '구멍'의 일부가 채워져 있음)

- 기본적으로 OpenCV는 3x3 사각형 구조 요소를 사용.
- 기본 구조 요소는 이 함수를 호출할 때의 세 번째 인자로 지정된 빈 행렬(cv::Mat())로 얻는다.
- 정의한 구조 요소를 갖는 행렬인 크기와 모양을 갖는 요소를 지정할 수 있다.
- cv::Mat element(7, 7, CV_8U, cv::Scalar(1)); // 7x7 구조 요소 적용
cv::erode(image, eroded, element);


-소스
*/
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
//    // 영상 침식
//    cv::Mat eroded; // 목적 영상
//    cv::Mat element(7, 7, CV_8U, cv::Scalar(1));
//    cv::erode(image, eroded, element); // 7x7 구조 요소를 적용
//    cv::namedWindow("Eroded Image (7x7)"); // 침식된 영상을 띄워봄
//    cv::imshow("Eroded Image (7x7)", eroded);
//
//    cv::Mat eroded1; // 목적 영상
//    cv::Mat element1(5, 5, CV_8U, cv::Scalar(1));
//    cv::erode(image, eroded1, element1); // 5x5 구조 요소를 적용
//    cv::namedWindow("Eroded Image (5x5)"); // 침식된 영상을 띄워봄
//    cv::imshow("Eroded Image (5x5)", eroded1);
//
//    cv::Mat eroded2; // 목적 영상
//    cv::Mat element2(3, 3, CV_8U, cv::Scalar(1));
//    cv::erode(image, eroded2, element2); // 3x3 구조 요소를 적용
//    cv::namedWindow("Eroded Image (3x3)"); // 침식된 영상을 띄워봄
//    cv::imshow("Eroded Image (3x3)", eroded2 );
//
//   // 구조에 따라 변화 확인하기.
//
//    cv::waitKey(0);
//
//    return 0;
//}
/*
-결과

- 같은 결과를 얻는 다른 방법 : 영상에 동일한 구조 요소를 반복적으로 적용하는 방법.
- 두 함수는 반복 횟수를 지정할 수 있는 부가적인 파라미터를 갖고 있음.

- 소스
*/
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
//    // 영상 침식
//    cv::Mat eroded; // 목적 영상
//    cv::erode(image, eroded, cv::Mat(), cv::Point(-1, -1), 3);
//    // 영상을 세 번 침식시키기
//    cv::namedWindow("Eroded Image (3)"); // 침식된 영상을 띄워봄
//    cv::imshow("Eroded Image (3)", eroded);
//
//    cv::waitKey(0);
//
//    return 0;
//}
/*
-결과

- 시작점 인자인 cv::Point(-1, -1)은 행렬 중심에 있는 시작점을 의미하고, 구조 요소 안에서 임의로 정의할 수 있다.
- 수행된 영상은 7x7 구조 요소로 얻은 결과와 동일.
- 영상을 두 번 침식하면 자신을 구조 요소로 팽창한 것이 침식한 영상과 동일하다.또한 팽창에도 적용됨.

- 배경 / 전경에 대한 개념은 임의로 정했는데, 침식 / 팽창 연산자의 기본 속성이라고 할 수 있다.
- 구조 요소로 침식시킨 전경 객체는 영상의 배경 부분을 팽창한 것으로 볼 수 있다.
- 영상의 침식은 보수 영상을 팽창시킨 결과의 보수와 동일하다.
- 영상의 팽창은 보수 영상을 침식시킨 결과의 보수와 동일하다.

부연 설명

- 동일한 정의로 그레에레벨 영상에 적용할 수 있다.
- 또한 형태학 함수는 내부 공간 처리를 지원한다. (대상 영상으로 입력 영상을 사용할 수 있음을 의미)
- cv::erode(image, image, cv::Mat()); // 올바르게 작동하기 위한 임시 영상을 생성함.
*/