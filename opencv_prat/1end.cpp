//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//// 영상을 생성하고 반환하는 함수
//cv::Mat function() {
//
//	// 영상 생성
//	cv::Mat ima(240, 320, CV_8U, cv::Scalar(100));
//	// 영상 반환
//	return ima;
//}
//
//int main() {
//
//	// 영상 생성
//	cv::Mat image;
//	// 영상 크기 출력
//	std::cout << "size: " << image.size().height << " , " << image.size().width << std::endl;
//	// 영상 열기
//	image = cv::imread("123.jpg");
//	// 영상을 성공적으로 열었는지 확인
//	if (!image.data) {
//		// no image has been created?
//		return 0;
//	}
//	// 영상 크기 출력
//	std::cout << "size (after reading): " << image.size().height << " , " << image.size().width << std::endl;
//
//	// 영상 띄워 보기
//	cv::namedWindow("Original Image"); // 창 정의
//	cv::imshow("Original Image", image); // 영상 보기
//
//										 // 다른 영  상 생성
//	cv::Mat result;
//	// 영상 뒤집기
//	cv::flip(image, result, 1); // 수평에   대한  양수
//								// 0은 수직,       
//								// 모두 음수임
//								// 결과 띄워 보기
//	cv::namedWindow("Output Image");
//	cv::imshow("Output Image", result);
//	// 키 입력 기다리기
//	cv::waitKey(0);
//	// 파일에 영상 쓰기
//	cv::imwrite("output.bmp", result);
//
//	// 두 개의 새로운 영상 생성
//	cv::Mat image2, image3;
//
//	image2 = result; // 동일한 데이터를 참조하는 두 영상
//	result.copyTo(image3); // 새로운 복사본이 생성됨
//
//						   // 수직으로 뒤집기
//	cv::flip(result, result, 0);
//
//	// 결과 띄워 보기
//	cv::namedWindow("image 2");
//	cv::imshow("image 2", image2);
//	cv::namedWindow("image 3");
//	cv::imshow("image 3", image3);
//
//	// 명암도 영상 가져오기
//	cv::Mat gray = function();
//	// 결과 띄워 보기
//	cv::namedWindow("Gray Image");
//	cv::imshow("Gray Image", gray);
//
//	// 키 입력 대기
//	cv::waitKey(0);
//	return 1;
//}
//
