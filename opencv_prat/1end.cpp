//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//// ������ �����ϰ� ��ȯ�ϴ� �Լ�
//cv::Mat function() {
//
//	// ���� ����
//	cv::Mat ima(240, 320, CV_8U, cv::Scalar(100));
//	// ���� ��ȯ
//	return ima;
//}
//
//int main() {
//
//	// ���� ����
//	cv::Mat image;
//	// ���� ũ�� ���
//	std::cout << "size: " << image.size().height << " , " << image.size().width << std::endl;
//	// ���� ����
//	image = cv::imread("123.jpg");
//	// ������ ���������� �������� Ȯ��
//	if (!image.data) {
//		// no image has been created?
//		return 0;
//	}
//	// ���� ũ�� ���
//	std::cout << "size (after reading): " << image.size().height << " , " << image.size().width << std::endl;
//
//	// ���� ��� ����
//	cv::namedWindow("Original Image"); // â ����
//	cv::imshow("Original Image", image); // ���� ����
//
//										 // �ٸ� ��  �� ����
//	cv::Mat result;
//	// ���� ������
//	cv::flip(image, result, 1); // ����   ����  ���
//								// 0�� ����,       
//								// ��� ������
//								// ��� ��� ����
//	cv::namedWindow("Output Image");
//	cv::imshow("Output Image", result);
//	// Ű �Է� ��ٸ���
//	cv::waitKey(0);
//	// ���Ͽ� ���� ����
//	cv::imwrite("output.bmp", result);
//
//	// �� ���� ���ο� ���� ����
//	cv::Mat image2, image3;
//
//	image2 = result; // ������ �����͸� �����ϴ� �� ����
//	result.copyTo(image3); // ���ο� ���纻�� ������
//
//						   // �������� ������
//	cv::flip(result, result, 0);
//
//	// ��� ��� ����
//	cv::namedWindow("image 2");
//	cv::imshow("image 2", image2);
//	cv::namedWindow("image 3");
//	cv::imshow("image 3", image3);
//
//	// ��ϵ� ���� ��������
//	cv::Mat gray = function();
//	// ��� ��� ����
//	cv::namedWindow("Gray Image");
//	cv::imshow("Gray Image", gray);
//
//	// Ű �Է� ���
//	cv::waitKey(0);
//	return 1;
//}
//
