//#include <opencv2/core/core.hpp>
//#include<iostream>
//#include <opencv2/highgui/highgui.hpp>
//
///*
//// 잡음 생성기.
//void salt(cv::Mat &image, int n) {
//
//
//	int i, j;
//
//	for (int k = 0; k<n; k++) {
//
//
//		// rand()는 MFC 임의 숫자 생성기이다
//
//		i = rand() % image.cols;
//
//		j = rand() % image.rows;
//
//
//
//		if (image.channels() == 1) { // 명암도 영상
//
//
//			image.at<uchar>(j, i) = 255;
//
//
//		}
//		else if (image.channels() == 3) { // 컬러 영상
//
//
//			image.at<cv::Vec3b>(j, i)[0] = 255;
//
//			image.at<cv::Vec3b>(j, i)[1] = 255;
//
//			image.at<cv::Vec3b>(j, i)[2] = 255;
//
//		}
//
//	}
//
//}
//
//
//int main()
//
//{
//
//	srand(cv::getTickCount()); // 임의 숫자 생성기 초기화
//
//
//	cv::Mat image = cv::imread("123.jpg", 0);
//
//
//	salt(image, 3000);
//
//
//	cv::namedWindow("Image");
//
//	cv::imshow("Image", image);
//
//
//	cv::imwrite("salted.bmp", image);
//
//
//	cv::waitKey(5000);
//
//
//	return 0;
//
//}
//*/
//
/////
//
//
//// .ptr와 [] 사용하기
//
//void colorReduce0(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int nc = image.cols * image.channels(); // 각 행에 있는 원소의 총 개수
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		uchar* data = image.ptr<uchar>(j);
//
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			data[i] = data[i] / div*div + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // end of line                   
//
//	}
//
//}
//
//
//// .ptr와 * ++ 사용하기 
//
//void colorReduce1(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int nc = image.cols * image.channels(); // 각 행에 있는 원소의 총 개수
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		uchar* data = image.ptr<uchar>(j);
//
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			*data++ = *data / div*div + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                   
//
//	}
//
//}
//
//
//// .ptr 와 * ++ 그리고 나머지 사용하기
//
//void colorReduce2(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int nc = image.cols * image.channels(); // 각 행에 있는 원소의 총 개수
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		uchar* data = image.ptr<uchar>(j);
//
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			int v = *data;
//
//			*data++ = v - v%div + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                   
//
//	}
//
//}
//
//
//// .ptr와 * ++ 그리고 비트별 연산
//
//void colorReduce3(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int nc = image.cols * image.channels(); // 각 행에 있는 원소의 총 개수
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// 화소값을 반올림하기 위해 사용하는 마스크
//
//	uchar mask = 0xFF << n; // 예, div=16이면 mask= 0xF0
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		uchar* data = image.ptr<uchar>(j);
//
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			*data++ = *data&mask + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                   
//
//	}
//
//}
//
//
//
//// 저수준 포인터 산술 연산
//
//void colorReduce4(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int nc = image.cols * image.channels(); // 각 행에 있는 원소의 총 개수
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	int step = image.step; // 유효 너비
//
//						   // 화소값을 반올림하기 위해 사용하는 마스크
//
//	uchar mask = 0xFF << n; // 예, for div=16이면 mask= 0xF0
//
//
//
//							// 영상 버퍼에 대한 포인터 가져오기
//
//	uchar *data = image.data;
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			*(data + i) = *data&mask + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                   
//
//
//		data += step;  // 다음 행
//
//	}
//
//}
//
//
//// image.cols * image.channels()로 .ptr와 * ++ 그리고 비트별 연산 
//
//void colorReduce5(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// 화소값을 반올림하기 위해 사용하는 마스크
//
//	uchar mask = 0xFF << n; // 예, for div=16이면 mask= 0xF0
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		uchar* data = image.ptr<uchar>(j);
//
//
//		for (int i = 0; i<image.cols * image.channels(); i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			*data++ = *data&mask + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                   
//
//	}
//
//}
//
//
//// .ptr와 * ++ 그리고 비트별 연산 (계속)
//
//void colorReduce6(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int nc = image.cols * image.channels(); // 각 행에 있는 원소의 총 개수
//
//
//	if (image.isContinuous()) {
//
//		// 더 이상 여분 화소가 없다면
//
//		nc = nc*nl;
//
//		nl = 1;  // 지금 1D 배열임
//
//	}
//
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// 화소값을 반올림하기 위해 사용하는 마스크
//
//	uchar mask = 0xFF << n; // 예, for div=16이면 mask= 0xF0
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		uchar* data = image.ptr<uchar>(j);
//
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			*data++ = *data&mask + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                  
//
//	}
//
//}
//
//
//// .ptr와 * ++ 그리고 비트별 연산 (계속+채널)
//
//void colorReduce7(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int nc = image.cols; // 열 개수
//
//
//	if (image.isContinuous()) {
//
//		// 더 이상 여분 화소가 없다면
//
//		nc = nc*nl;
//
//		nl = 1;  // 지금 1D 배열임
//
//	}
//
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// 화소값을 반올림하기 위해 사용하는 마스크
//
//	uchar mask = 0xFF << n; // 예, for div=16이면 mask= 0xF0
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		uchar* data = image.ptr<uchar>(j);
//
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			*data++ = *data&mask + div / 2;
//
//			*data++ = *data&mask + div / 2;
//
//			*data++ = *data&mask + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                   
//
//	}
//
//}
//
//
//
//// Mat_ 반복자 사용 
//
//void colorReduce8(cv::Mat &image, int div = 64) {
//
//
//	// 반복자 가져오기
//
//	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
//
//	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
//
//
//	for (; it != itend; ++it) {
//
//
//
//		// 각 화소에 대한 처리 ---------------------
//
//
//		(*it)[0] = (*it)[0] / div*div + div / 2;
//
//		(*it)[1] = (*it)[1] / div*div + div / 2;
//
//		(*it)[2] = (*it)[2] / div*div + div / 2;
//
//
//		// 각 화소 처리 끝 ----------------
//
//	}
//
//}
//
//
//// Mat_ iterator와 비트별 연산 사용
//
//void colorReduce9(cv::Mat &image, int div = 64) {
//
//
//	// 2의 지수승으로 반드시 나눠야 함
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// 화소값을 반올림하기 위해 사용하는 마스크
//
//	uchar mask = 0xFF << n; // 예, for div=16이면 mask= 0xF0
//
//
//							// 반복자 가져오기
//
//	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
//
//	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
//
//
//	// 모든 화소 조회
//
//	for (; it != itend; ++it) {
//
//
//
//		// 각 화소에 대한 처리 ---------------------
//
//
//		(*it)[0] = (*it)[0] & mask + div / 2;
//
//		(*it)[1] = (*it)[1] & mask + div / 2;
//
//		(*it)[2] = (*it)[2] & mask + div / 2;
//
//
//		// 각 화소 처리 끝 ----------------
//
//	}
//
//}
//
//
//// MatIterator_ 사용하기
//
//void colorReduce10(cv::Mat &image, int div = 64) {
//
//
//	// 반복자 가져오기
//
//	cv::Mat_<cv::Vec3b> cimage = image;
//
//	cv::Mat_<cv::Vec3b>::iterator it = cimage.begin();
//
//	cv::Mat_<cv::Vec3b>::iterator itend = cimage.end();
//
//
//	for (; it != itend; it++) {
//
//
//
//		// 각 화소에 대한 처리 ---------------------
//
//
//		(*it)[0] = (*it)[0] / div*div + div / 2;
//
//		(*it)[1] = (*it)[1] / div*div + div / 2;
//
//		(*it)[2] = (*it)[2] / div*div + div / 2;
//
//
//		// 각 화소 처리 끝 ----------------
//
//	}
//
//}
//
//
//
//void colorReduce11(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // 행 개수
//
//	int nc = image.cols; // 열 개수
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			image.at<cv::Vec3b>(j, i)[0] = image.at<cv::Vec3b>(j, i)[0] / div*div + div / 2;
//
//			image.at<cv::Vec3b>(j, i)[1] = image.at<cv::Vec3b>(j, i)[1] / div*div + div / 2;
//
//			image.at<cv::Vec3b>(j, i)[2] = image.at<cv::Vec3b>(j, i)[2] / div*div + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                   
//
//	}
//
//}
//
//
//// 입력/결과 영상과 함께
//
//void colorReduce12(const cv::Mat &image, // 입력 영상
//
//	cv::Mat &result,      // 결과 영상
//
//	int div = 64) {
//
//
//	int nl = image.rows; // 열 개수
//
//	int nc = image.cols; // 행 개수
//
//
//						 // 필요 시 결과 영상 할당
//
//	result.create(image.rows, image.cols, image.type());
//
//
//	// 여분 화소를 갖지 않는 영상 생성
//
//	nc = nc*nl;
//
//	nl = 1;  // 지금 1D 배열임
//
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// 화소값을 반올림하기 위해 사용하는 마스크
//
//	uchar mask = 0xFF << n; // 예, for div=16이면 mask= 0xF0
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//
//		uchar* data = result.ptr<uchar>(j);
//
//		const uchar* idata = image.ptr<uchar>(j);
//
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// 각 화소에 대한 처리 ---------------------
//
//
//
//			*data++ = (*idata++)&mask + div / 2;
//
//			*data++ = (*idata++)&mask + div / 2;
//
//			*data++ = (*idata++)&mask + div / 2;
//
//
//
//			// 각 화소 처리 끝 ----------------
//
//
//
//		} // 행 끝                
//
//	}
//
//}
//
//
//// 오버로드한 연산자 사용
//
//void colorReduce13(cv::Mat &image, int div = 64) {
//
//
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// 화소값을 반올림하기 위해 사용하는 마스크
//
//	uchar mask = 0xFF << n; // 예, for div=16이면 mask= 0xF0
//
//
//							// 컬러 감축 수행
//
//	image = (image&cv::Scalar(mask, mask, mask)) + cv::Scalar(div / 2, div / 2, div / 2);
//
//}
//
//
//
//#define NTESTS 14
//
//#define NITERATIONS 20
//
//
//int main()
//
//{
//
//	int64 t[NTESTS], tinit;
//
//	cv::Mat image1;
//
//	cv::Mat image2;
//
//
//	// 타이머를 0으로 설정
//
//	for (int i = 0; i<NTESTS; i++)
//
//		t[i] = 0;
//
//
//	// 여러 번 실험 반복
//
//	int n = NITERATIONS;
//
//	for (int k = 0; k<n; k++) {
//
//
//		std::cout << k << " of " << n << std::endl;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		if (!image1.data)
//
//			return 0;
//
//
//		// .ptr와 [] 사용하기
//
//		tinit = cv::getTickCount();
//
//		colorReduce0(image1);
//
//		t[0] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// .ptr와 * ++ 사용하기
//
//		tinit = cv::getTickCount();
//
//		colorReduce1(image1);
//
//		t[1] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// .ptr와 * ++ 그리고 나머지 사용하기
//
//		tinit = cv::getTickCount();
//
//		colorReduce2(image1);
//
//		t[2] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// .ptr와* ++ 그리고 비트별 연산
//
//		tinit = cv::getTickCount();
//
//		colorReduce3(image1);
//
//		t[3] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// 저수준 포인터 산술 연산 사용하기
//
//		tinit = cv::getTickCount();
//
//		colorReduce4(image1);
//
//		t[4] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		//  image.cols * image.channels()로 .ptr와 * ++ 그리고 비트별 연산
//
//		tinit = cv::getTickCount();
//
//		colorReduce5(image1);
//
//		t[5] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// .ptr와 * ++ 그리고 비트별 연산 사용하기(계속)
//
//		tinit = cv::getTickCount();
//
//		colorReduce6(image1);
//
//		t[6] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// .ptr와 * ++ 그리고 비트별 연산(계속+채널)
//
//		tinit = cv::getTickCount();
//
//		colorReduce7(image1);
//
//		t[7] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// Mat_ 반복자 사용하기
//
//		tinit = cv::getTickCount();
//
//		colorReduce8(image1);
//
//		t[8] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// Mat_ 반복자와 비트별 연산 사용하기
//
//		tinit = cv::getTickCount();
//
//		colorReduce9(image1);
//
//		t[9] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// Mat_ 반복자 사용하기
//
//		tinit = cv::getTickCount();
//
//		colorReduce10(image1);
//
//		t[10] += cv::getTickCount() - tinit;
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// 여기서 사용
//
//		tinit = cv::getTickCount();
//
//		colorReduce11(image1);
//
//		t[11] += cv::getTickCount() - tinit;
//
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// 입력/결과 영상 사용하기
//
//		tinit = cv::getTickCount();
//
//		cv::Mat result;
//
//		colorReduce12(image1, result);
//
//		t[12] += cv::getTickCount() - tinit;
//
//
//		image2 = result;
//
//
//
//		image1 = cv::imread("salted.jpg");
//
//		// 입력/결과 영상 사용하기
//
//		tinit = cv::getTickCount();
//
//		colorReduce13(image1);
//
//		t[13] += cv::getTickCount() - tinit;
//
//
//		//------------------------------
//
//	}
//
//
//
//	cv::namedWindow("Result");
//
//	cv::imshow("Result", image2);
//
//	cv::namedWindow("Image Result");
//
//	cv::imshow("Image Result", image1);
//
//
//	// print average execution time
//
//	std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;
//
//	std::cout << "using .ptr and [] =" << 1000.*t[0] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using .ptr and * ++ =" << 1000.*t[1] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using .ptr and * ++ and modulo =" << 1000.*t[2] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using .ptr and * ++ and bitwise =" << 1000.*t[3] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using direct pointer arithmetic =" << 1000.*t[4] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using .ptr and * ++ and bitwise with image.cols * image.channels() =" << 1000.*t[5] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using .ptr and * ++ and bitwise (continuous) =" << 1000.*t[6] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using .ptr and * ++ and bitwise (continuous+channels) =" << 1000.*t[7] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using Mat_ iterator =" << 1000.*t[8] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using Mat_ iterator and bitwise =" << 1000.*t[9] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using MatIterator_ =" << 1000.*t[10] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using at =" << 1000.*t[11] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using input/output images =" << 1000.*t[12] / cv::getTickFrequency() / n << "ms" << std::endl;
//
//	std::cout << "using overloaded operators =" << 1000.*t[13] / cv::getTickFrequency() / n << "ms" << std::endl;
// 
//
//
//	cv::waitKey();
//
//	return 0;
//
//}
