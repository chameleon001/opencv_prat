//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//void colorReduce(cv::Mat &image, int div = 64) {
//
//    int nl = image.rows; // �� ����
//    int nc = image.cols; // �� ����
//
//    for (int j = 0; j<nl; j++) {
//        for (int i = 0; i<nc; i++) {
//            // �� ȭ�ҿ� ���� ó��
//            image.at<cv::Vec3b>(j, i)[0] = image.at<cv::Vec3b>(j, i)[0] / div*div + div / 2;
//            image.at<cv::Vec3b>(j, i)[1] = image.at<cv::Vec3b>(j, i)[1] / div*div + div / 2;
//            image.at<cv::Vec3b>(j, i)[2] = image.at<cv::Vec3b>(j, i)[2] / div*div + div / 2;
//            // �� ȭ�� ó�� �� ----------------
//        } // �� ��                   
//    }
//}
//
//
////�÷� ���� ����.
//void color_colorReduce(cv::Mat &image, int div = 64) {
//
//    int nl = image.rows; // �� ����
//    int nc = image.cols; // �� ����
//
//    if (image.isContinuous()) { // ���ӵ� �����ΰ�.
//        nc = nc * nl; // ä�� ȭ�Ұ� ���ٸ�...
//        nl = 1; // ������ 1���� �迭
//    }
//
//    int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//    // ȭ�Ұ��� �ݿø��� �� ����ϴ� ����ũ
//    uchar mask = 0xFF << n; // ���� ��� div=16, mask=0xF0 
//
//    for (int j = 0; j<nl; j++) { // ��� ȭ�Ҹ� �������
//        uchar* data = image.ptr<uchar>(j);
//        for (int i = 0; i<nc; i++) {
//            // �� ȭ�ҿ� ���� ó��
//            *data++ = *data&mask + div / 2;
//            *data++ = *data&mask + div / 2;
//            *data++ = *data&mask + div / 2;
//            // �� ȭ�� ó�� �� ----------------
//        } // �� ��                   
//    }
//}
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//
//    double duration;
//    // �Լ��� �ڵ��� ����ð��� �����ϴµ� cv::getTickCount() ���
//    duration = static_cast<double>(cv::getTickCount());
//    // cv::getTickCount() : ��ǻ�͸� ������ �ĺ��� ������ �ð��� �߻��ϴ� Ŭ�� ����Ʋ ��
//    std::cout << "duration : " << duration << std::endl;
//
//    colorReduce(image);
//
//    duration = static_cast<double>(cv::getTickCount()) - duration;
//    std::cout << "getTickCount()-duration : " << duration << std::endl;
//    duration /= cv::getTickFrequency();
//    std::cout << "getTickFrequency() : " << duration << std::endl;
//    // cv::getTickFrequency() : �и��� ������ �ڵ� �κ��� ����ð� �˾Ƴ�
//    // ms ������ ��� �ð�
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
