//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//void colorReduce(cv::Mat &image, int div = 64) {
//    // ������ ���ø� �޼ҵ�.
//    // �ݺ��ڴ� cv::MaIterator_<cv::Vec3b> it; �Ǵ�,
//    // cv::Mat_<cv::Vec3b>::iterator it; ���� ����.
//    // �ݺ��ڴ� ��ȯ Ÿ���� ��õǾ�� �Ѵ�.
//    // �÷� ������ ó���ϱ� ������ cv:Vec3b�� ��ȯ.
//    cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
//    // �ʱ� ��ġ���� �ݺ��� ���
//    cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
//    // ������ ��ġ���� ���
//
//    for (; it != itend; ++it) { // ��� ȭ�Ҹ� ��ȸ
//                                // �� ȭ�ҿ� ���� ó��
//        (*it)[0] = (*it)[0] / div*div + div / 2; // ������ ���� ĳ����
//        (*it)[1] = (*it)[1] / div*div + div / 2;
//        (*it)[2] = (*it)[2] / div*div + div / 2;
//        // �� ȭ�� ó�� ��
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