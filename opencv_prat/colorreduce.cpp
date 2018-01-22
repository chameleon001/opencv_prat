//
//�����ε�� ���� ������
//
//- ��κ� ��� �Լ��� �ش� �����ڸ� �����ε� �ϱ� ������ cv::addWeighted�� ȣ���Ϸ��� ���� �ڵ�� �� �� �ִ�.
//- result = 0.7*image1 + 0.9*image2; (���� ���� ���� �� ���� ����� ����)
//- cv::saturate_cast �Լ��� ���� ��쿡�� ������ ȣ���Ѵ�.
//
//- C++ ������ �����ε� : ��Ʈ ������ &, | , ^, ~, min, max, abs �Լ�.�� ������ <, <= , == , != , >=
//    -��� �� m1*m2(m1�� m2 ��� cv : Mat �ν��Ͻ�), ����� m1.inv(), ��ġ��� m1.t(), ��Ľ� m1.determinant(), ���� �� v1.norm(), ���� v1.aross(v2), ���� v1.dot(v2)
//
//    - ���� ȭ�Ҹ� ��ȸ�ϴ� �ݺ����� ����� �÷� ���� �Լ��� ���⼭ �Է� ���� ���� ��� ������ ����� �Լ��� ������ �ٽ� �� �� �ִ�.
//    - image = (image&cv::Scalar(mask, mask, mask)) + cv::Scalar(div / 2, div / 2, div / 2);
//
//-cv::Scalar�� �÷� ������ �ٷ�� ������ ���.
//- And�� ��Į�� ��(���� �ݺ��� ���� ��ü �۾��� �����ϴ� ���)�� ȣ�������� �� �ڵ尡 �ſ� �ܼ�������.
//
//- �ҽ�

//
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//void colorReduce(cv::Mat &image, int div = 64) {
//    int nl = image.rows;
//    int nc = image.cols*image.channels();
//    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//    // ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//    uchar mask = 0xFF << n; // ��, div=16�̸� mask= 0xF0
//
//    image = (image&cv::Scalar(mask, mask, mask)) + cv::Scalar(div / 2, div / 2, div / 2);
//    // ���� ȭ�Ҹ� ��ȸ�ϴ� �ݺ����� ����� �÷� ���� �Լ��� ������ ���� ������ �� �� �ִ�.
//}
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//    cv::Mat background = cv::imread("456.jpg");
//    cv::Mat result;
//
//    result = 0.8*image + 0.4*background; // ������ �����ε�
//
//    cv::namedWindow("Result");
//    cv::imshow("Result", result);
//
//    colorReduce(image); // �÷� ���� �Լ� ȣ��
//
//    cv::namedWindow("Result2");
//    cv::imshow("Result2", image);
//
//    cv::waitKey(0);
//
//    return 0;
//}

//-���
//
//���� ä�� �и�
//
//- ������ �� ä���� ���������� ó���� �� �ִ�.
//- �̴� ���� ��ȸ �ݺ������� ���� �� �ִ�.
//- �÷� ������ �� ���� ä���� �� ������ ���� �ٸ� cv : Mat �ν��Ͻ��� �����ϴ� cv::split �Լ��� ����� �� �ִ�.
//
//- �ҽ�
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <vector>
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//    cv::Mat background = cv::imread("456.jpg", 0); // ������ ó�� (�׷��̷��� �����̾�� ��)
//    cv::Mat result;
//
//    std::vector<cv::Mat> planes; // 3�� ������ ���� ����
//    cv::split(image, planes); // 3ä�� ���� ������ �� 1ä�� �������� �и�
//    planes[2] += background; // �Ķ� ä�� ��ġ��
//                             // planes[1]�̸� �ʷ� ä�� ��ġ��
//                             // planes[2]�̸� ���� ä�� ��ġ��
//    cv::merge(planes, result); // 3���� 1ä���� 3ä���� ���� ���� �������� ����
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
