//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//class ColorHistogram {
//private:
//    int histSize[3];
//    float hranges[2];
//    const float* ranges[3];
//    int channels[3];
//public:
//    ColorHistogram() {
//        // �÷� ������׷��� ���� ���� �غ�
//        histSize[0] = histSize[1] = histSize[2] = 256;
//        hranges[0] = 0.0;    // BRG ����
//        hranges[1] = 255.0;
//        ranges[0] = hranges; // ��� ä���� ���� ������ ���� 
//        ranges[1] = hranges;
//        ranges[2] = hranges;
//        channels[0] = 0;  // �� ���� ä�� 
//        channels[1] = 1;
//        channels[2] = 2;
//    }
//
//    // ������׷� ���.
//    cv::MatND getHistogram(const cv::Mat &image) {
//
//        cv::MatND hist;
//
//        // BGR �÷� ������׷�
//        hranges[0] = 0.0;    // BRG ����
//        hranges[1] = 255.0;
//        channels[0] = 0;  // �� ���� ä��
//        channels[1] = 1;
//        channels[2] = 2;
//
//        // ������׷� ���
//        cv::calcHist(&image,
//            1,   // ���� ������ ������׷���
//            channels, // ��� ä��
//            cv::Mat(), //����ũ ������� ����
//            hist,  // ��� ������׷�
//            3,   // 3D ������׷�
//            histSize, // �󵵼�
//            ranges  // ȭ�Ұ� ����
//            );
//
//        return hist;
//    }
//
//    // ������׷� ���.
//    cv::SparseMat getSparseHistogram(const cv::Mat &image) {
//
//        cv::SparseMat hist(3, histSize, CV_32F);
//
//        // BGR �÷� ������׷�
//        hranges[0] = 0.0;    // BRG ����
//        hranges[1] = 255.0;
//        channels[0] = 0;  // �� ���� ä�� 
//        channels[1] = 1;
//        channels[2] = 2;
//
//        // Compute histogram
//        cv::calcHist(&image,
//            1,   // ���� ������ ������׷���
//            channels, // ��� ä��
//            cv::Mat(), // ����ũ ������� ����      
//            hist,  // ��� ������׷�   
//            3,   // 3D ������׷�          
//            histSize, // �󵵼�                 
//            ranges  // ȭ�Ұ� ����            
//            );
//
//        return hist;
//    }
//
//    cv::Mat colorReduce(const cv::Mat &image, int div = 64) {
//
//        int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
//        // ȭ�Ұ� �ݿø� �ϱ� ���� ����ϴ� ����ũ
//        uchar mask = 0xFF << n; // ��, div=16�̸� mask= 0xF0
//
//        cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
//        cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
//
//        // ��� ���� ����(�׻� 1-ä��)
//        cv::Mat result(image.rows, image.cols, image.type());
//        cv::Mat_<cv::Vec3b>::iterator itr = result.begin<cv::Vec3b>();
//
//        for (; it != itend; ++it, ++itr) {
//
//            (*itr)[0] = ((*it)[0] & mask) + div / 2;
//            (*itr)[1] = ((*it)[1] & mask) + div / 2;
//            (*itr)[2] = ((*it)[2] & mask) + div / 2;
//        }
//
//        return result;
//    }
//};
//
//class ImageComparator {
//private:
//    cv::Mat reference; // ����
//    cv::Mat input; // ���� ���
//    cv::MatND refH;
//    cv::MatND inputH;
//
//    ColorHistogram hist;
//    int div;
//
//public:
//    ImageComparator() : div(32) { // div=32 �ʱ�ȭ
//    }
//
//    // �ŷ��� �� �ִ� ���絵 ���� ����� �������� �÷� ������ �ݵ�� �����ؾ� ��
//    // Ŭ������ �÷� ���� ���ڸ� �����ϸ�, ���ǿ� �Է� ���� ��� ����
//    void setColorReduction(int factor) {
//        // �÷� ���� ����
//        // �� ������ ���ڿ� ���� �÷� ���� ���� ��Ų ���� ��
//        div = factor;
//    }
//
//    int getColorReduction() {
//        return div;
//    }
//
//    void setReferenceImage(const cv::Mat& image) {
//        // ���� ���� ������ ���͸� ����� ����, ���� ���� ���� �÷��� ����
//        reference = hist.colorReduce(image, div);
//        refH = hist.getHistogram(reference);
//    }
//
//    double compare(const cv::Mat& image) {
//        // compare �޼ҵ�� ������ �Է� ����� ���� ������ ��
//        // �� ������ �󸶳� �������� �˷��ִ� ���� ��ȯ
//        input = hist.colorReduce(image, div);
//        inputH = hist.getHistogram(input);
//
//        return cv::compareHist(refH, inputH, CV_COMP_INTERSECT);
//    }
//};
//
//int main()
//{
//
//    cv::Mat image = cv::imread("123.jpg"); // ���� ���� �б�
//    cv::namedWindow("god do");
//    cv::imshow("god do", image); // ���� ��� ����
//     
//    ImageComparator c;
//    c.setReferenceImage(image);
//    // �� Ŭ������ �־��� ���� ����� ������ ������ �˻��ϴ� �� ���
//
//    cv::Mat input = cv::imread("salted.jpg");
//    cv::namedWindow("god_salted do");
//    cv::imshow("god_salted", input); // ���� ��� ����
//
//    std::cout << "god do vs god_salted: " << c.compare(input) << std::endl;
//    // ���� ����� �� 
//
//    cv::waitKey(0);
//
//    return 0;
//}
//
///*
//
//- ��κ� ������׷� �� ������ �� ���� �񱳸� ������� ��.
//- ������׷��� �󵵸� ���� �� �̿��� �󵵸� ������� �ʴ´�.
//- ���� �� �÷� ������׷��� ���絵�� �����ϱ� ���� �÷� ������ �����ϴ� ���� �߿�.
//
//- cv::compareHist�� ȣ���ϴ� ����� ����.
//- �� ������׷��� �ٷ� �Է��ϰ� �� �Լ����� ������ �Ÿ��� ��ȯ�Ѵ�.
//- �÷��׸� ����ϱ� ���ϴ� ���� ����� �����Ѵ�.
//- ImageComparator Ŭ�������� ���ͼ��� ����� ���(CV_Comp_INTERSECT �÷��׸� �Բ� ���)�Ѵ�.
//- �� ����� �����ϰ� �� ��, �� �� ������׷� ���� �� �� ���� ���ϰ�, �� �� �ּڰ��� ����, ���絵 ������ �ּҰ��� ������ ����������.
//- �̷� ��� ��� �÷��� ���� ���� ȭ���� �� ������ ������ �� ������׷��� ���� �� ������ ���ͼ��� ���� 0�̴�.
//
//- ����� �� �ִ� �ٸ� ����� ī�� ����(CV_COMP_CHISQR �÷���)�̸�, �� �� ���� ���� ������ ������ ���Ѵ�.
//- ī�� ���� ����
//- ������� ���(CV_COMP_CORREL �÷���)�� ��ȣ ó������ �� ��ȣ ���� ���絵�� �����ϱ� ���� ����ϴ� ���� �������� ������.
//- ��Ÿí���� ����(CV_COMP_BHATTACHARYYA �÷���)�� �� Ȯ�� ���� ���� ���絵�� �����ϱ� ���� ���� ���.
//*/