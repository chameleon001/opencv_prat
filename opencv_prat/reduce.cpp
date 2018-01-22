#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void colorReduce(cv::Mat &image, int div = 64) {
	int nl = image.rows;
	int nc = image.cols*image.channels();

	for (int j = 0; j<nl; j++) {
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i<nc; i++) {
			// 阿 拳家 贸府
			int v = *data;
			*data++ = v - v%div + div / 2;
			// 阿 拳家 贸府 场
		} // 青 场
	}
}

int main()
{
	cv::Mat image = cv::imread("123.jpg");

	colorReduce(image);

	cv::namedWindow("Image");
	cv::imshow("Image", image);
	cv::waitKey(5000);

	return 0;
}

