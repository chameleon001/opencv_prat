//#include <opencv2/core/core.hpp>
//#include<iostream>
//#include <opencv2/highgui/highgui.hpp>
//
///*
//// ���� ������.
//void salt(cv::Mat &image, int n) {
//
//
//	int i, j;
//
//	for (int k = 0; k<n; k++) {
//
//
//		// rand()�� MFC ���� ���� �������̴�
//
//		i = rand() % image.cols;
//
//		j = rand() % image.rows;
//
//
//
//		if (image.channels() == 1) { // ��ϵ� ����
//
//
//			image.at<uchar>(j, i) = 255;
//
//
//		}
//		else if (image.channels() == 3) { // �÷� ����
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
//	srand(cv::getTickCount()); // ���� ���� ������ �ʱ�ȭ
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
//// .ptr�� [] ����ϱ�
//
//void colorReduce0(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols * image.channels(); // �� �࿡ �ִ� ������ �� ����
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//
//			data[i] = data[i] / div*div + div / 2;
//
//
//
//			// �� ȭ�� ó�� �� ----------------
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
//// .ptr�� * ++ ����ϱ� 
//
//void colorReduce1(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols * image.channels(); // �� �࿡ �ִ� ������ �� ����
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//
//			*data++ = *data / div*div + div / 2;
//
//
//
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                   
//
//	}
//
//}
//
//
//// .ptr �� * ++ �׸��� ������ ����ϱ�
//
//void colorReduce2(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols * image.channels(); // �� �࿡ �ִ� ������ �� ����
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//
//			int v = *data;
//
//			*data++ = v - v%div + div / 2;
//
//
//
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                   
//
//	}
//
//}
//
//
//// .ptr�� * ++ �׸��� ��Ʈ�� ����
//
//void colorReduce3(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols * image.channels(); // �� �࿡ �ִ� ������ �� ����
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//
//	uchar mask = 0xFF << n; // ��, div=16�̸� mask= 0xF0
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//
//			*data++ = *data&mask + div / 2;
//
//
//
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                   
//
//	}
//
//}
//
//
//
//// ������ ������ ��� ����
//
//void colorReduce4(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols * image.channels(); // �� �࿡ �ִ� ������ �� ����
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	int step = image.step; // ��ȿ �ʺ�
//
//						   // ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//
//	uchar mask = 0xFF << n; // ��, for div=16�̸� mask= 0xF0
//
//
//
//							// ���� ���ۿ� ���� ������ ��������
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//
//			*(data + i) = *data&mask + div / 2;
//
//
//
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                   
//
//
//		data += step;  // ���� ��
//
//	}
//
//}
//
//
//// image.cols * image.channels()�� .ptr�� * ++ �׸��� ��Ʈ�� ���� 
//
//void colorReduce5(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//
//	uchar mask = 0xFF << n; // ��, for div=16�̸� mask= 0xF0
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//
//			*data++ = *data&mask + div / 2;
//
//
//
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                   
//
//	}
//
//}
//
//
//// .ptr�� * ++ �׸��� ��Ʈ�� ���� (���)
//
//void colorReduce6(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols * image.channels(); // �� �࿡ �ִ� ������ �� ����
//
//
//	if (image.isContinuous()) {
//
//		// �� �̻� ���� ȭ�Ұ� ���ٸ�
//
//		nc = nc*nl;
//
//		nl = 1;  // ���� 1D �迭��
//
//	}
//
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//
//	uchar mask = 0xFF << n; // ��, for div=16�̸� mask= 0xF0
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//
//			*data++ = *data&mask + div / 2;
//
//
//
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                  
//
//	}
//
//}
//
//
//// .ptr�� * ++ �׸��� ��Ʈ�� ���� (���+ä��)
//
//void colorReduce7(cv::Mat &image, int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols; // �� ����
//
//
//	if (image.isContinuous()) {
//
//		// �� �̻� ���� ȭ�Ұ� ���ٸ�
//
//		nc = nc*nl;
//
//		nl = 1;  // ���� 1D �迭��
//
//	}
//
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//
//	uchar mask = 0xFF << n; // ��, for div=16�̸� mask= 0xF0
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
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
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                   
//
//	}
//
//}
//
//
//
//// Mat_ �ݺ��� ��� 
//
//void colorReduce8(cv::Mat &image, int div = 64) {
//
//
//	// �ݺ��� ��������
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
//		// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//		(*it)[0] = (*it)[0] / div*div + div / 2;
//
//		(*it)[1] = (*it)[1] / div*div + div / 2;
//
//		(*it)[2] = (*it)[2] / div*div + div / 2;
//
//
//		// �� ȭ�� ó�� �� ----------------
//
//	}
//
//}
//
//
//// Mat_ iterator�� ��Ʈ�� ���� ���
//
//void colorReduce9(cv::Mat &image, int div = 64) {
//
//
//	// 2�� ���������� �ݵ�� ������ ��
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//
//	uchar mask = 0xFF << n; // ��, for div=16�̸� mask= 0xF0
//
//
//							// �ݺ��� ��������
//
//	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
//
//	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
//
//
//	// ��� ȭ�� ��ȸ
//
//	for (; it != itend; ++it) {
//
//
//
//		// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//		(*it)[0] = (*it)[0] & mask + div / 2;
//
//		(*it)[1] = (*it)[1] & mask + div / 2;
//
//		(*it)[2] = (*it)[2] & mask + div / 2;
//
//
//		// �� ȭ�� ó�� �� ----------------
//
//	}
//
//}
//
//
//// MatIterator_ ����ϱ�
//
//void colorReduce10(cv::Mat &image, int div = 64) {
//
//
//	// �ݺ��� ��������
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
//		// �� ȭ�ҿ� ���� ó�� ---------------------
//
//
//		(*it)[0] = (*it)[0] / div*div + div / 2;
//
//		(*it)[1] = (*it)[1] / div*div + div / 2;
//
//		(*it)[2] = (*it)[2] / div*div + div / 2;
//
//
//		// �� ȭ�� ó�� �� ----------------
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
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols; // �� ����
//
//
//
//	for (int j = 0; j<nl; j++) {
//
//		for (int i = 0; i<nc; i++) {
//
//
//
//			// �� ȭ�ҿ� ���� ó�� ---------------------
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
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                   
//
//	}
//
//}
//
//
//// �Է�/��� ����� �Բ�
//
//void colorReduce12(const cv::Mat &image, // �Է� ����
//
//	cv::Mat &result,      // ��� ����
//
//	int div = 64) {
//
//
//	int nl = image.rows; // �� ����
//
//	int nc = image.cols; // �� ����
//
//
//						 // �ʿ� �� ��� ���� �Ҵ�
//
//	result.create(image.rows, image.cols, image.type());
//
//
//	// ���� ȭ�Ҹ� ���� �ʴ� ���� ����
//
//	nc = nc*nl;
//
//	nl = 1;  // ���� 1D �迭��
//
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//
//	uchar mask = 0xFF << n; // ��, for div=16�̸� mask= 0xF0
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
//			// �� ȭ�ҿ� ���� ó�� ---------------------
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
//			// �� ȭ�� ó�� �� ----------------
//
//
//
//		} // �� ��                
//
//	}
//
//}
//
//
//// �����ε��� ������ ���
//
//void colorReduce13(cv::Mat &image, int div = 64) {
//
//
//
//	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//
//	// ȭ�Ұ��� �ݿø��ϱ� ���� ����ϴ� ����ũ
//
//	uchar mask = 0xFF << n; // ��, for div=16�̸� mask= 0xF0
//
//
//							// �÷� ���� ����
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
//	// Ÿ�̸Ӹ� 0���� ����
//
//	for (int i = 0; i<NTESTS; i++)
//
//		t[i] = 0;
//
//
//	// ���� �� ���� �ݺ�
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
//		// .ptr�� [] ����ϱ�
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
//		// .ptr�� * ++ ����ϱ�
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
//		// .ptr�� * ++ �׸��� ������ ����ϱ�
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
//		// .ptr��* ++ �׸��� ��Ʈ�� ����
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
//		// ������ ������ ��� ���� ����ϱ�
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
//		//  image.cols * image.channels()�� .ptr�� * ++ �׸��� ��Ʈ�� ����
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
//		// .ptr�� * ++ �׸��� ��Ʈ�� ���� ����ϱ�(���)
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
//		// .ptr�� * ++ �׸��� ��Ʈ�� ����(���+ä��)
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
//		// Mat_ �ݺ��� ����ϱ�
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
//		// Mat_ �ݺ��ڿ� ��Ʈ�� ���� ����ϱ�
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
//		// Mat_ �ݺ��� ����ϱ�
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
//		// ���⼭ ���
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
//		// �Է�/��� ���� ����ϱ�
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
//		// �Է�/��� ���� ����ϱ�
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
