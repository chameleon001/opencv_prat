////-영상은 일반 행렬이므로 더하기, 빼기, 곱하기, 나누기가 가능.
////- 이번 예제에서는 두 영상을 더하는데, 몇 가지 특수 효과를 만들거나 영상 위에 정보를 겹쳐 쓰길 원할 때 유용하다.
////
////- cv::add 함수 또는 좀 더 정확하게 가중 합을 넣기 원할 때 cv::addWeighted 함수를 호출.
////- cv::addWeighted(image1, 0.7, image2, 0.9, 0., result);
////
////
////
//
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//    cv::Mat background = cv::imread("456.jpg");
//    cv::Mat result;
//
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//
//    cv::namedWindow("Background");
//    cv::imshow("Background", background);
//
//    cv::addWeighted(image, 0.8, background, 0.4, 0, result);
//    // result = 0.8*image + 0.4*background + 0
//
//    cv::namedWindow("Result");
//    cv::imshow("Result", result);
//
//    cv::waitKey(0);
//
//    return 0;
//}
//
////
////
////예제 분석
////
////- 제공된 두 입력과 세 번째 파라미터를 결과로 지정.
////- 어떤 경우에도 가중치를 연산할 때 스칼라 곱으로 지정할수 있음.
////- 각 함수는 몇 가지로 파생되며 cv : add는 다양한 형태에서 활용할 수 있는 함수의 좋은 예.
////- cv::add(imageA, imageB, resultC); // c[i]=a[i]+b[i]
////-cv::add(imageA, cv::Scalar(k), resultC); // c[i]=a[i]+k
////-cv::addWeighted(imageA, k1, imageB, k2, k3, resultC);
////
////// c[i]=k1*a[i]+k2*b[i]+k3
////
////-cv::scaleAdd(imageA, k, imageB, resultC); // c[i]=k*a[i]+b[i];
////
////
////-일부 함수에서는 마스크도 지정 가능.
////- cv::add(imageA, imageB, resultC, mask) // if(mask[i]) c[i]=a[i]+b[i];
////- 마스크를 적용할 경우 마스크 값이 널(마스크는 1채널)이 아닌 경우에 한해 해당 화소에 수행한다.
////
////- 함수의 다른 형태 : cv::substract, cv::absdiff, cv::multiplay, cv::divide
////- 비트 연산자 : cv::bitwise_and, cv::bitwise_or, cv::bitwise_xor, cv::bitwise_not
////- 화소별 최대 최소값 : cv::min, cv::max
////
////- cv::saturate_cast : 모든 경우 결과가 정의된 화소값 영역(오버플로우, 언더플로우를 피하기 위해)에 들어가는지 확인하기 위해 사용(OpenCV #2 - 5 Example 이웃 접근으로 영상 조회 - 소스 참조)
////
////- 영상은 같은 크기와 타입이어야 함.
////- 연산은 화소별로 수행하므로, 입력 영상 중 하나는 결과 영상으로 사용할 수 있음.
////
////- 입력 영상인 단일 영상을 취하는 연산 : cv::sqrt, cv::pow, cv::abs, cv::cuberoot, cv::exp, cv::log
