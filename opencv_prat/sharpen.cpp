////-���ö�þ� ������(������ ������)
////- ���� ���ö�ð��� ��ģ ����� ���� ���� ������ �ε巯���� �� ������ ������ ��.
////- sharpened_pixel = 5 * current - left - right - up - down;
////-current�� ���, left�� �ٷ� ���� �� ���� ������ ȭ��, up�� ���� ���� ����� ���� �ϴ� ȭ���̴�.
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
//    // �ʿ��ϸ� �Ҵ�
//    // create�� ������ ������� Ÿ���� �Ȱ��� �������
//
//    for (int j = 1; j<image.rows - 1; j++) { // ��� �࿡ ����(ó���� �������� �����ϰ�)
//        const uchar* previous = image.ptr<const uchar>(j - 1); // ���� ��
//        const uchar* current = image.ptr<const uchar>(j); // ���� ��
//        const uchar* next = image.ptr<const uchar>(j + 1); // ���� ��
//        uchar* output = result.ptr<uchar>(j); // ��� ��
//
//        for (int i = 1; i<image.cols - 1; i++) {
//            *output++ = cv::saturate_cast<uchar>(5 * current[i] + current[i - 1] - current[i + 1] - previous[i] - next[i]);
//            output[i] = cv::saturate_cast<uchar>(5 * current[i] - current[i - 1] - current[i + 1] - previous[i] - next[i]);
//        }
//    }
//    // ó������ �ʴ� ȭ�Ҹ� 0���� ����
//    result.row(0).setTo(cv::Scalar(0));
//    result.row(result.rows - 1).setTo(cv::Scalar(0));
//    result.col(0).setTo(cv::Scalar(0));
//    result.col(result.cols - 1).setTo(cv::Scalar(0));
//}
//
///*
//- �̿� ȭ�ҿ� ���� ����� ������ ��κ� Ŀ�� ����� ǥ��.
//- ���� �������� ����� ������ ���Ϳ��� Ŀ���� ������ ����.
//0  -1  0
//-1  5  -1
//0  -1  0
//
//- ���� ��õ��� ������ ���� ȭ�Ҵ� Ŀ���� �߽ɿ� ����.
//- Ŀ�� �� �� ���� �ִ� ���� ��ġ�ϴ� ȭ�ҿ� ���ϴ� ���ڸ� �ǹ�.
//- ȭ�ҿ� ���� Ŀ���� ������ ����� ��� ������ ��. Ŀ���� ũ��� �̿� ũ�⿡ ����.
//- ����ȭ ���Ϳ��� �� �� �ֵ� ���� ȭ���� �� ���� ����� ���� �̿��� -1�� ���ϴµ�, ����� 5�� ���Ѵ�.
//
//- ���͸��� ����ó������ �Ϲ����� �۾��̹Ƿ�, OpenCV�� cv::filter2D�Լ��� �ش� �۾��� �����Ѵ�. - ����ȭ �Լ� (����ϱ� ���ؼ��� Ŀ�� - ��� ���·� �����ؾ� ��)
//*/
//void sharpen2D(const cv::Mat &image, cv::Mat &result) {
//    cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
//    // Ŀ�� ����(��� ���� 0���� �ʱ�ȭ)
//    kernel.at<float>(1, 1) = 5.0; // Ŀ�� ���� �Ҵ�
//    kernel.at<float>(0, 1) = -1.0;
//    kernel.at<float>(2, 1) = -1.0;
//    kernel.at<float>(1, 0) = -1.0;
//    kernel.at<float>(1, 2) = -1.0;
//
//    cv::filter2D(image, result, image.depth(), kernel);
//    // ���� ���͸�
//}
//
//void color_sharpen2D(const cv::Mat &image, cv::Mat &result) {
//    cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0, 0, 0));
//    // Ŀ�� ����(��� ���� 0���� �ʱ�ȭ)
//    kernel.at<float>(1, 1) = 5.0;// Ŀ�� ���� �Ҵ�
//    kernel.at<float>(0, 1) = -1.0;
//    kernel.at<float>(2, 1) = -1.0;
//    kernel.at<float>(1, 0) = -1.0;
//    kernel.at<float>(1, 2) = -1.0;
//
//    cv::filter2D(image, result, image.depth(), kernel);
//    // ���� ���͸�
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
//    cv::Mat image2 = cv::imread("123.jpg"); // imread �ڿ� 0�Ⱥ��̸� �÷�
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
////���� �м�
////
////- ���� ��� ���� ���� �̿� ȭ�ҿ� �����Ϸ��� �ٸ� �ϳ��� ���ؼ� ������ �����͸� �߰��� �����ϸ� ���� ������ �����Ѵ�.
////- cv::staturate_cast�� 0���� 255�̸��̶�� ȭ�Ұ� ��� ������ ����� ��찡 ���� �ִ�.
////- cv::staturate_cast<uchar>�Լ��� �̿��ؼ� ���� ���� 0����, 255 �̻� ���� 255�� ��ȯ�Ѵ�.
////
////- �̿��� ������ �������� �ʾұ� ������ �׵θ� ȭ�Ҹ� ó���� �� ��� ������ �ٷ���ϸ�, ���⼭�� 0���� �����Ѵ�.
////- row�� col �޼ҵ带 ����� �׵θ� ȭ�Ҹ� 0���� ����.
////- setTo : ��� ��� ��ҿ� ���� ���� �Ҵ�.
////- result.row(0).setTo(cv::Scalar(0)); // ������ ù ��° �࿡ �ִ� ��� ȭ�ҿ� 0�� �Ҵ�
////-3ä�� �÷� �����̸� �� ä�� ȭ�ҿ� �Ҵ��ϴ� �� ���� ���� �����ϴ� cv::Scalar(a, b, c) ���.