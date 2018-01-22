/*
-������ ���� ������.
- ����� ������ ���͸� �����Ϸ��� cv::morphologyEx �Լ��� ����ؾ� ��.
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
//    // �Է� ���� �б�
//
//    cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
//    // ���� ȿ���� �� �ε巯���� 5x5 ���� ��Ҹ� ���
//
//    // �ݱ� ������ ����
//    cv::Mat closed;
//    cv::morphologyEx(image, closed, cv::MORPH_CLOSE, element5);
//    cv::namedWindow("Closed Image");
//    cv::imshow("Closed Image", closed);
//
//    // ���� ������ ����
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

- ����� ���� ���ʹ� �⺻ ħ�İ� ��â ���� �������� ������ ���� �Ѵ�.
- ������ ħ���� ������ ��â���� �����Ѵ�.
- ������ ��â�� ������ ħ������ �����Ѵ�.
- ��, ������ ���� ȣ���� ������ ħ���� ����� �� �ִ�.
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
//    // ���� ���� (������ ħ�� ���)
//    cv::Mat result;
//    cv::dilate(image, result, cv::Mat()); // �� ������ ��â
//    cv::erode(result, result, cv::Mat()); // ��â�� ���� ���� ħ��
//    cv::namedWindow("Closed Filter");
//    cv::imshow("Closed Filter", result);
//
//    // ���� ���� (������ ��â ���)
//    cv::Mat result2;
//    cv::erode(image, result2, cv::Mat()); // �� ������ ħ��
//    cv::dilate(result2, result2, cv::Mat()); // ħ�ĵ� ���� ���� ��â
//    cv::namedWindow("Opened Filter");
//    cv::imshow("Opened Filter", result2);
//
//    cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
//    // ���� ȿ���� �� �ε巯���� 5x5 ���� ��Ҹ� ���
//
//    // ���� ������ ���� ����
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


- ���� ���� : �Ͼ�� ���� ��ü�� ���� ������ ä�������� �� �� �ְ�, ������ ���� ��ü�� �Բ� ������.���� ��Ҹ� �����ϱ⿣ �ſ� ���� ������ Ȧ�̳� ������ �����Ѵ�.
- ���� ���� : ��� ���� ���� ���� ��ü�� �����Ѵ�.���� ��Ҹ� �����ϱ⿡ �ſ� ���� ���� ��� �����Ѵ�.

- �� ���ʹ� ��ü ������ ���� ���.
- ���� ���Ͱ� ���� �������� ���� ���� ����� ����.
- ���� ���Ͱ� �߸��� ������ ��ü�� ���� �κ����� �Բ� ����. (��, ������� �� ���͸� ����ϴ� ���� ����)
- ������ ���� ������ ������� �ݰ� ���� Closed and Opened Image�� ��� ó�� ��� ���� �ֿ� ��ü�� �ִ� ������ ��´�.

- �ش� ���� ���� ���� �Ǵ� ���� �����ڸ� ���� �� �����ص� �ƹ��� ȿ���� ����.
- ù ��° ������ ���� ������ ä�����ٸ� ���� �� ���͸� �߰��� �����ص� �ش� ���� �ƹ��� ��ȭ�� ���� �ʴ´�.
- �̷� �����ڸ� ���� ���� �����ڰ� ����� �ȴٰ� �Ѵ�.f(x) = f(f(x))
*/