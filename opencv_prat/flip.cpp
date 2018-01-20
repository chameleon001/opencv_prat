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
//	cv::namedWindow("Original Image"); // 창을 정의
//	cv::imshow("Original Image", image); // 영상을 보여 주기
//
//	cv::Mat result; // 영상을 담을 변수 선언
//	cv::flip(image, result, 1); // 1 왼쪽 오른쪽 0 위 아래
//
//	// flie은 영상을 반전시키는 메소드
//	// 수평을 의미하는 양수, 0은 수직, 음수는 수직 수평
//
//	cv::namedWindow("Output Image"); // 다른 창에서 결과를 띄움
//	cv::imshow("Output image", result);
////	cv::waitKey(0);
//
//	cv::Mat result2;
//	cv::flip(result, result2, 0);
//	cv::namedWindow("Output Image2");
//	cv::imshow("Output image22~", result2);
//	cv::waitKey(0);
//
//	cv::imwrite("output.bmp", result); // 영상 저장
//
//	return 1;
//}
//
