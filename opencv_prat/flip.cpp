//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//using namespace std;
////using namespace cv;
//
//int main()
//{
//	cv::Mat image;
//	cout << "size : " << image.size().height << ", " << image.size().width << std::endl;
//	image = cv::imread("123.jpg");
//
//	if (!image.data)
//	{
//		cout << "Create failed" << endl;
//	}
//
//	cv::namedWindow("Original Image"); // â�� ����
//	cv::imshow("Original Image", image); // ������ ���� �ֱ�
//
//	cv::Mat result; // ������ ���� ���� ����
//	cv::flip(image, result, 1); // 1 ���� ������ 0 �� �Ʒ�
//
//	// flie�� ������ ������Ű�� �޼ҵ�
//	// ������ �ǹ��ϴ� ���, 0�� ����, ������ ���� ����
//
//	cv::namedWindow("Output Image"); // �ٸ� â���� ����� ���
//	cv::imshow("Output image", result);
////	cv::waitKey(0);
//
//	cv::Mat result2;
//	cv::flip(result, result2, 0);
//	cv::namedWindow("Output Image2");
//	cv::imshow("Output image22~", result2);
//	cv::waitKey(0);
//
//	cv::imwrite("output.bmp", result); // ���� ����
//
//	return 1;
//}
//
