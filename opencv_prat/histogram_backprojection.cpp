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
//
//}; // ������׷� ������ �˰��򿡼� �÷� ������ ����� �� �ִ� ���
//   // ���� ������ ó�� ������ ĸ��ȭ�� Ŭ������ ����
//   // �ʿ��� �Ӽ��� �ʱ� �����͸� ����
//class ContentFinder {
//private:
//    float hranges[2];
//    const float* ranges[3];
//    int channels[3];
//    float threshold;
//    cv::MatND histogram;
//public:
//    ContentFinder() : threshold(-1.0f) {
//        ranges[0] = hranges; // ��� ä���� ������ ������ ����
//        ranges[1] = hranges;
//        ranges[2] = hranges;
//    }
//
//    // ���� ����� �����ֱ� ���� ���� ���� ������ �� ����ϴ� ��谪 �Ķ���͸� ����
//    // �Ķ���͸� ���� ������ �����ϸ� ���� Ȯ�� ���� ��ȯ
//    void setThreshold(float t) {
//        // ������׷� ���� [0,1]���� ��谪 ����
//        threshold = t;
//    }
//
//    float getThreshold() {
//        // ��谪 ��������
//        return threshold;
//    }
//
//    // �Է� ������׷��� �ݵ�� ����ȭ �Ǿ�� ��
//    void setHistogram(const cv::MatND& h) {
//        // ���� ������׷� ����
//        histogram = h;
//        cv::normalize(histogram, histogram, 1.0);
//    }
//
//    cv::Mat find(const cv::Mat& image) {
//        // ������׷��� ���ϴ� ȭ�� ã��
//        cv::Mat result;
//
//        hranges[0] = 0.0; // [0,255] ����
//        hranges[1] = 255.0;
//        channels[0] = 0;  // �� ���� ä�� 
//        channels[1] = 1;
//        channels[2] = 2;
//
//        cv::calcBackProject(&image, // �Է� ����
//            1,            // �� �� �� ���� ���
//            channels,     // ���� ä�ο� ���ϴ� ������׷� ������ ���� ����            
//            histogram,   // ������׷� ���                                           
//            result,       // ������ ���� ���                                          
//            ranges,       // �� ������ ���� �� ����                                    
//            255.0         // ������׷��� 1�� 255�� �����ϱ� ���� ������ �����ϸ� ���� 
//            );
//
//        if (threshold>0.0) {
//            // ���� ������ ��� ���� ������ ��谪
//            cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
//        }
//
//        return result;
//    }
//
//    // ������׷��� �������Ϸ��� ����� ����(��� ä���� ���⼭ ������ ������ ���´ٰ� ����),
//    // ����ϴ� ä�� ����� �����ϰ� ������ �ʿ䰡 �ִ�.
//    cv::Mat find(const cv::Mat& image, float minValue, float maxValue, int *channels, int dim) {
//
//        cv::Mat result;
//
//        hranges[0] = minValue;
//        hranges[1] = maxValue;
//
//        for (int i = 0; i<dim; i++)
//            this->channels[i] = channels[i];
//
//        cv::calcBackProject(&image, // �Է� ����
//            1,            // �� �� �� ���� ���
//            channels,     // ���� ä�ο� ���ϴ� ������׷� ������ ���� ����            
//            histogram,   // ������׷� ���                                           
//            result,       // ������ ���� ���                                          
//            ranges,       // �� ������ ���� �� ����                                    
//            255.0         // ������׷��� 1�� 255�� �����ϱ� ���� ������ �����ϸ� ���� 
//            );
//
//        if (threshold>0.0) {
//            //���� ������ ��� ���� ������ ��谪
//            cv::threshold(result, result, 255 * threshold, 255, cv::THRESH_BINARY);
//        }
//        return result;
//    }
//};
//
//int main()
//{
//    cv::Mat color = cv::imread("123.jpg");
//
//    if (!color.data)
//        return 0;
//
//    cv::namedWindow("Image");
//    cv::imshow("Image", color);
//
//    ColorHistogram hc;
//    color = hc.colorReduce(color, 32);
//    cv::namedWindow("Color Image");
//    cv::imshow("Color Image", color);
//
//    cv::Mat imageROI = color(cv::Rect(0, 0, 165, 75)); // �Ķ� �ϴ� ����
//    //image �� ���ɿ���(ROI�� ����)
//    //�ϴ� �����̾��� ���������� �״�� ���..
//    cv::MatND hist = hc.getHistogram(imageROI);
//    ContentFinder finder;
//    finder.setHistogram(hist);
//    finder.setThreshold(0.05f);
//    cv::Mat result = finder.find(color);
//    // ������׷��� ����ϰ� ������ �ϴ� �Ϻθ� �����ϱ� ���� find �޼ҵ� ���
//  //  cv::imwrite("gray.jpg", result);
//    cv::namedWindow("Color Backproject Result");
//    cv::imshow("Color Backproject Result", result);
//  
//    cv::waitKey(0);
//
//    return 0;
//}