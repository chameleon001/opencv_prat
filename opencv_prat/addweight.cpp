////-������ �Ϲ� ����̹Ƿ� ���ϱ�, ����, ���ϱ�, �����Ⱑ ����.
////- �̹� ���������� �� ������ ���ϴµ�, �� ���� Ư�� ȿ���� ����ų� ���� ���� ������ ���� ���� ���� �� �����ϴ�.
////
////- cv::add �Լ� �Ǵ� �� �� ��Ȯ�ϰ� ���� ���� �ֱ� ���� �� cv::addWeighted �Լ��� ȣ��.
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
////���� �м�
////
////- ������ �� �Է°� �� ��° �Ķ���͸� ����� ����.
////- � ��쿡�� ����ġ�� ������ �� ��Į�� ������ �����Ҽ� ����.
////- �� �Լ��� �� ������ �Ļ��Ǹ� cv : add�� �پ��� ���¿��� Ȱ���� �� �ִ� �Լ��� ���� ��.
////- cv::add(imageA, imageB, resultC); // c[i]=a[i]+b[i]
////-cv::add(imageA, cv::Scalar(k), resultC); // c[i]=a[i]+k
////-cv::addWeighted(imageA, k1, imageB, k2, k3, resultC);
////
////// c[i]=k1*a[i]+k2*b[i]+k3
////
////-cv::scaleAdd(imageA, k, imageB, resultC); // c[i]=k*a[i]+b[i];
////
////
////-�Ϻ� �Լ������� ����ũ�� ���� ����.
////- cv::add(imageA, imageB, resultC, mask) // if(mask[i]) c[i]=a[i]+b[i];
////- ����ũ�� ������ ��� ����ũ ���� ��(����ũ�� 1ä��)�� �ƴ� ��쿡 ���� �ش� ȭ�ҿ� �����Ѵ�.
////
////- �Լ��� �ٸ� ���� : cv::substract, cv::absdiff, cv::multiplay, cv::divide
////- ��Ʈ ������ : cv::bitwise_and, cv::bitwise_or, cv::bitwise_xor, cv::bitwise_not
////- ȭ�Һ� �ִ� �ּҰ� : cv::min, cv::max
////
////- cv::saturate_cast : ��� ��� ����� ���ǵ� ȭ�Ұ� ����(�����÷ο�, ����÷ο츦 ���ϱ� ����)�� ������ Ȯ���ϱ� ���� ���(OpenCV #2 - 5 Example �̿� �������� ���� ��ȸ - �ҽ� ����)
////
////- ������ ���� ũ��� Ÿ���̾�� ��.
////- ������ ȭ�Һ��� �����ϹǷ�, �Է� ���� �� �ϳ��� ��� �������� ����� �� ����.
////
////- �Է� ������ ���� ������ ���ϴ� ���� : cv::sqrt, cv::pow, cv::abs, cv::cuberoot, cv::exp, cv::log
