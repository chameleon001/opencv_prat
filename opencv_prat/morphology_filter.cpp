//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//// ���� Ư¡�� ������ �� �ִ� Ŭ����
//class MorphoFeatures {
//private:
//    int threshold; // ���� ������ ����� ���� ��谪 
//                   // �ڳ� ������ ����ϴ� ���� ���
//    cv::Mat cross;
//    cv::Mat diamond;
//    cv::Mat square;
//    cv::Mat x;
//
//    // ���� ���� ������ ��´�
//    void applyThreshold(cv::Mat& result) {
//        // ����� ��谪 ����
//        if (threshold>0)
//            cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY_INV);
//    }
//
//public:
//    cv::Mat getEdges(const cv::Mat &image) {
//        cv::Mat result;
//        cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
//        // ���� ���� ��������
//
//        applyThreshold(result);
//        // ���� ������ ��� ���� ��谪 ����
//
//        return result;
//    }
//
//    void setThreshold(int t) {
//        threshold = t;
//    }
//
//    int getThreshold() const {
//        return threshold;
//    }
//};
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg");
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//
//    // ���� ���� ���
//    MorphoFeatures morpho; // ������ Ư¡ �ν��Ͻ� ����
//    morpho.setThreshold(30);
//
//    cv::Mat edges; // ���� ��������
//    edges = morpho.getEdges(image);
//
//    cv::namedWindow("Edge Image");
//    cv::imshow("Edge Image", edges);
//
//    cv::waitKey(0);
//
//    return 0;
//}
//

///*
//- ������ ���͸� �̿��� �ڳ� ������ OpenCV�� ���� ������ �� ���� ������ �ణ �� �����ϴ�.
//- ��簢�� ���� ��Ҹ� ����ؾ� �ϸ�, �簢��, ���̾Ƹ��, ���ڰ�, X ��� ���� ���ǵ� �� ���� ���� ��� ����� �ʿ�.
//- �̰͵��� ������(��� ���� ��Ҵ� ����ȭ�� ���� 5x5 ������ ���´�)���� �̷�����.
//*/

//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//// ���� Ư¡�� ������ �� �ִ� Ŭ����
//class MorphoFeatures {
//private:
//    int threshold; // ���� ������ ����� ���� ��谪 
//                   // �ڳ� ������ ����ϴ� ���� ���
//    cv::Mat cross;
//    cv::Mat diamond;
//    cv::Mat square;
//    cv::Mat x;
//
//    // ���� ���� ������ ��´�
//    void applyThreshold(cv::Mat& result) {
//        // ����� ��谪 ����
//        if (threshold>0)
//            cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY_INV);
//    }
//
//public:
//    cv::Mat getEdges(const cv::Mat &image) {
//        cv::Mat result;
//        cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
//        // ���� ���� ��������
//
//        applyThreshold(result);
//        // ���� ������ ��� ���� ��谪 ����
//
//        return result;
//    }
//
//    void setThreshold(int t) {
//        threshold = t;
//    }
//
//    int getThreshold() const {
//        return threshold;
//    }
//
//    // ������ - ��� ���� ��Ҵ� ����ȭ�� ���� 5x5 ������ ���´�.
//    MorphoFeatures() : threshold(-1),
//        cross(5, 5, CV_8U, cv::Scalar(0)), // ���ڰ�
//        diamond(5, 5, CV_8U, cv::Scalar(1)), // �پ��̸��
//        square(5, 5, CV_8U, cv::Scalar(1)), // �簢��
//        x(5, 5, CV_8U, cv::Scalar(0)) { // x ���
//
//                                        // ���ڰ� ����� ���� ���� ��� ����
//        for (int i = 0; i<5; i++) {
//            cross.at<uchar>(2, i) = 1;
//            cross.at<uchar>(i, 2) = 1;
//        }
//
//        // ���̾Ƹ�� ����� ���� ���� ��� ����
//        diamond.at<uchar>(0, 0) = 0;
//        diamond.at<uchar>(0, 1) = 0;
//        diamond.at<uchar>(1, 0) = 0;
//        diamond.at<uchar>(4, 4) = 0;
//        diamond.at<uchar>(3, 4) = 0;
//        diamond.at<uchar>(4, 3) = 0;
//        diamond.at<uchar>(4, 0) = 0;
//        diamond.at<uchar>(4, 1) = 0;
//        diamond.at<uchar>(3, 0) = 0;
//        diamond.at<uchar>(0, 4) = 0;
//        diamond.at<uchar>(0, 3) = 0;
//        diamond.at<uchar>(1, 4) = 0;
//
//        // x ����� ���� ���� ��� ����
//        for (int i = 0; i<5; i++) {
//            x.at<uchar>(i, i) = 1;
//            x.at<uchar>(4 - i, i) = 1;
//        }
//    }
//
//    // �ڳ� Ư¡�� ������ �� ��� �ڳ� ���� ��� ����
//    // ��� ���� ��Ҹ� ������� ����
//    cv::Mat getCorners(const cv::Mat &image) {
//        cv::Mat result;
//        cv::dilate(image, result, cross);
//        // ���ڰ��� ��â 
//        cv::erode(result, result, diamond);
//        // ���̾Ƹ��� ħ��
//
//        cv::Mat result2;
//        cv::dilate(image, result2, x);
//        // X�� ��â
//
//        cv::erode(result2, result2, square);
//        // �簢������ ħ��
//        cv::absdiff(result2, result, result);
//        // �� ���� ���� ���� ���̰����� �ڳ� ���
//        applyThreshold(result);
//        // ���� ������ ��� ���� ��谪 ����
//
//        return result;
//    }
//
//    // ���� ����� �� ���� �����ַ��� ���� �޼ҵ忡�� ���� ����
//    // �� ������ ���� �̿��� ���� ���� ���� �׷���
//    void drawOnImage(const cv::Mat& binary, cv::Mat& image) {
//        cv::Mat_<uchar>::const_iterator it = binary.begin<uchar>();
//        cv::Mat_<uchar>::const_iterator itend = binary.end<uchar>();
//
//        for (int i = 0; it != itend; ++it, ++i) { // �� ȭ�Һ��� 
//            if (!*it)
//                cv::circle(image, cv::Point(i%image.step, i / image.step), 5, cv::Scalar(255, 0, 0));
//        }
//    }
//};
//
//int main()
//{
//    cv::Mat image = cv::imread("123.jpg", 0);
//    cv::namedWindow("Image");
//    cv::imshow("Image", image);
//
//    // ���� ���� ���
//    MorphoFeatures morpho; // ������ Ư¡ �ν��Ͻ� ����
//    morpho.setThreshold(-1);
//
//    // ���󿡼� �ڳ� ����
//    cv::Mat corners;
//    corners = morpho.getCorners(image); // �ڳ� ��������
//    cv::morphologyEx(corners, corners, cv::MORPH_TOPHAT, cv::Mat());
//    cv::threshold(corners, corners, 40, 255, cv::THRESH_BINARY_INV);
//    cv::namedWindow("Corner Image");
//    cv::imshow("Corner Image", corners); // �ڳ� ���� ��� ����
//
//    morpho.drawOnImage(corners, image); // �ڳ� �׸���
//    cv::namedWindow("Concers on Image");
//    cv::imshow("Concers on Image", image); // ���� �� �ڳ� ����
//
//    cv::waitKey(0);
//
//    return 0;
//}

///*
//���� �м�
//
//- �׷��̷��� ���� ���� ������ �������� ȿ���� �����ϴ� �� ������ �Ǵ� ��� : �ع�(�Ǵ� ��)�� �����ϴ� �׷��̷����� �� ������ ��ü���� �ִ� ������ ����ϴ� ��.
//- ���� ������ �꿡 �����ϰ�, ��ο� ������ ���� ���� �� ����.
//- ������ ��ο� ȭ�ҿ� ���� ȭ�� ������ �ް��� ��ȭ�� �����ϵ� ���ĸ� �������� ���� ����.
//- ħ�� �����ڸ� �̷� ������ �����ϸ� �׹� ����� Ư�� ���� ���� �� ȭ�Ҹ� ���� ������ ��ġ�ϹǷ�, ������ ���̸� ���߰� �ȴ�.
//- ��, ������ ����� Ȯ��� 'ħ��' �̴�.
//- ��â�� ���ݴ��� ȿ���� ���µ�, ������ ��� ���� �ִ� ������ �ȴ�.
//- �׷��� ���(������ ��ϵ��� ���� ����)�� ������� ������ �ʴ´�.
//
//- ������ ����(�Ǵ� ����)�� �����ϴ� ����� ħ�ĵ� ����� ��â�� ������ ���̸� ����� ���� �� �ִ�.
//- �� ��ȯ ������ ���� ��ġ�� �ַ� ���̰� �ֱ� ������ �� ���̷� ���� ���� ������ �ε巯����.
//- cv::MORPH_GRADIENT ���ڸ� �Է��� cv::morphologyEx �Լ��� ��Ȯ�ϰ� �����Ѵ�.
//- ū ���� ��Ҵ� ������ ������ ���Ⱑ �ȴ�.
//- ���� ���� �����ڴ� �ٿ�ó ����(���� ����� #6���� ����)��� �Ѵ�.
//- ������ ����δ� �����ϰ� ��â�� ���󿡼� �� ������ ���ų�, Ȥ�� �� ���󿡼� ħ���� ������ ���� ���� �� �ִ�.
//- ��� ������ �ܼ��� ��� ��.
//
//- �ڳ� ������ �� ���� ���� ��Ҹ� ����ϱ� ������ �� ����.
//- �ڳ� �����ڴ� OpenCV���� ���� �������� �ʱ� ������ ���⼭ ���� ����� ���� ��Ҹ� �����ϰ� �����ϴ� ����� �������.
//- �� ���̵��� �� ���� ���� �ٸ� ���� ��ҿ�, ��â�� ħ�Ŀ� ���� ���� ������ �ִ�.
//- �� ��Ҵ� ������ �ٷ� ���ϴ� �κ��� ����������, �ش� ȿ���� ���� �ڳ� ���� ������ ������ ��ģ��.
//- ���Ī ���� ���꿡 ���� ������ ���� �����Ϸ��� ���� ��� �簢������ ���� ���� ������ ����غ���.
//*/
//
//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//int main()
//{
//    cv::Mat image;
//    // �簢�� ������ �а� ��� ����
//    image = cv::imread("123.jpg", 0);
//    cv::namedWindow("Square Image");
//    cv::imshow("Square Image", image);
//
//    // ���ڰ� ����� ���� ��� ����
//    cv::Mat cross(5, 5, CV_8U, cv::Scalar(0));
//    for (int i = 0; i<5; i++) {
//        cross.at<uchar>(2, i) = 1;
//        cross.at<uchar>(i, 2) = 1;
//    }
//
//    // ���ڰ��� ��â 
//    cv::Mat result;
//    cv::dilate(image, result, cross);
//
//    // ��� ��� ����
//    cv::namedWindow("Dilated square with cross");
//    cv::imshow("Dilated square with cross", result);
//
//    // ���̾Ƹ�� ����� ������� ����
//    cv::Mat diamond(5, 5, CV_8U, cv::Scalar(1));
//    diamond.at<uchar>(0, 0) = 0;
//    diamond.at<uchar>(0, 1) = 0;
//    diamond.at<uchar>(1, 0) = 0;
//    diamond.at<uchar>(4, 4) = 0;
//    diamond.at<uchar>(3, 4) = 0;
//    diamond.at<uchar>(4, 3) = 0;
//    diamond.at<uchar>(4, 0) = 0;
//    diamond.at<uchar>(4, 1) = 0;
//    diamond.at<uchar>(3, 0) = 0;
//    diamond.at<uchar>(0, 4) = 0;
//    diamond.at<uchar>(0, 3) = 0;
//    diamond.at<uchar>(1, 4) = 0;
//
//    // ���̾Ƹ��� ħ��
//    cv::Mat result2;
//    cv::erode(result, result2, diamond);
//
//    // ��� ��� ����
//    cv::namedWindow("Eroded square with diamond");
//    cv::imshow("Eroded square with diamond", result2);
//
//    // ������ �ϳ��� �����ϱ�
//    cv::Mat final(100, 300, CV_8U);
//    cv::Mat window = final(cv::Rect(0, 0, 100, 100));
//    image.copyTo(window);
//    window = final(cv::Rect(100, 0, 100, 100));
//    result.copyTo(window);
//    window = final(cv::Rect(200, 0, 100, 100));
//    result2.copyTo(window);
//
//    // ���� ����� ��� ����
//    cv::namedWindow("Combined");
//    cv::imshow("Combined", final);
//
//    cv::waitKey();
//
//    return 0;
//}

/*
-���
"Square Image"
"Dilated square with cross"
"Eroded square with diamond"

- ���ڰ� ����� ���� ��ҷ� ��â���� �� �ڳ����� �����ϸ� �簢�� ������ Ȯ��Ǵµ�, ���ڰ� ����� ���簢���� �ǵ帮�� �ʴ´�. (�߰� �簢��)
- ��â �̹����� ���� ��ҷ� ħ��, �� ���̾Ƹ�� ����� ���´�.
- ħ���� �� ��ġ�� ��κ� ������ ������, �ڳʿ� ���ص� �� �̻� ��â���� �ʾҴ�.
- ������ �簢���� ��� �ڳʸ� �Ҿ��µ�, ������ ������ X ���� �簢�� ��� ���� ��Ҹ� ���� �ݺ��Ѵ�.
- ���� ������ ȸ���� �� ��Ҵ� ����� 45�� ���⿡�� �ڳʸ� ����.
- ������ �� ����� ���̷� ���� �ڳ� Ư¡�� ����.

*/