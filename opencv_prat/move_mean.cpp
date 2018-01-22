//#include <iostream>
//#include <vector>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/video/tracking.hpp>
//#include <opencv2/video/video.hpp>
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
//    // ����ũ�� �Բ� 1���� ���� ������׷� ���
//    // BGR ���� ������ HSV�� ��ȯ
//    // ���� ä���� ���� ȭ�Ҹ� ����
//    cv::MatND getHueHistogram(const cv::Mat &image, int minSaturation = 0) {
//        cv::MatND hist;
//        cv::Mat hsv; // HSV �÷� ���� ��ȯ
//        cv::cvtColor(image, hsv, CV_BGR2HSV); // HSV �������� ��ȯ
//        cv::Mat mask; // ����ϴ� ����ũ (�Ǵ� ������� ����)
//
//        if (minSaturation > 0) {
//            std::vector<cv::Mat> v; // 3ä���� 3�� �������� �и�
//            cv::split(hsv, v); // ���� �и�
//            cv::threshold(v[1], mask, minSaturation, 255, cv::THRESH_BINARY);
//            // ���� ä�� ȭ�Ҹ� ����ũ�� ����
//        }
//
//        // 1���� ���� ������׷� ���� �غ�
//        hranges[0] = 0.0;
//        hranges[1] = 180.0;
//        channels[0] = 0; // ���� ä��
//        cv::calcHist(&hsv, // ������׷� ��� 
//            1,   // ���� ������ ������׷���
//            channels, // ��� ä��               
//            cv::Mat(), // ����ũ ���α׷�         
//            hist,  // ��� ������׷�         
//            1,   // 1D ������׷�           
//            histSize, // �󵵼�                  
//            ranges  // ȭ�Ұ� ����             
//            );
//        return hist;
//    }
//};
//
//// ������׷� ������ �˰��򿡼� �÷� ������ ����� �� �ִ� ���
//// ���� ������ ó�� ������ ĸ��ȭ�� Ŭ������ ����
//// �ʿ��� �Ӽ��� �ʱ� �����͸� ����
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
//    cv::Mat image = cv::imread("move.jpg");
//    // ���� ���� �б�
//    //cv::Mat imageROI = image(cv::Rect(110, 260, 35, 40));
//    // ������ �� ROI
//    cv::Mat imageROI = image(cv::Rect(100, 95, 85, 82));
//    cv::namedWindow("Image1");
//    cv::imshow("Image1", image);
//
//    int minSat = 65;
//    ColorHistogram hc; // ���� ������׷� ��������
//    cv::MatND colorhist = hc.getHueHistogram(imageROI, minSat);
//
//    ContentFinder finder;
//    finder.setHistogram(colorhist);
//    // ��� ������׷��� �Է����� ContentFinder Ŭ���� �ν��Ͻ��� ����
//    finder.setThreshold(0.2f);
//
//    // HSV �������� ��ȯ
//    cv::Mat hsv;
//    cv::cvtColor(image, hsv, CV_BGR2HSV);
//
//    std::vector<cv::Mat> v; // 3ä���� 3�� �������� �и�
//    cv::split(hsv, v); // ���� �и�
//
//    cv::threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
//    // ���� ä���� ���� ȭ�� ����
//    cv::namedWindow("Saturation");
//    cv::imshow("Saturation", v[1]);
//
//    int ch[1] = { 0 };
//    cv::Mat result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//    // ���� ������׷��� ������ ��������
//    cv::namedWindow("Result Hue");
//    cv::imshow("Result Hue", result);
//
//    cv::bitwise_and(result, v[1], result);
//    cv::namedWindow("Result Hue and");
//    cv::imshow("Result Hue and", result);
//
////    cv::rectangle(image, cv::Rect(110, 260, 35, 40), cv::Scalar(0, 0, 255));
//
//    cv::rectangle(image, cv::Rect(100, 95, 85, 82), cv::Scalar(0, 0, 255));
//
//    cv::namedWindow("Image 1 result");
//    cv::imshow("Image 1 result", image);
//   //cv::rectangle(image, cv::Rect(110, 260, 35, 40), cv::Scalar(0, 255, 0));
//    cv::rectangle(image, cv::Rect(100, 95, 85, 82), cv::Scalar(0, 255, 0));
//
//    image = cv::imread("move2.jpg");
//    // ���ο� ������ ���� ��ġ�� ã�� ���ϴ� �� ��° ���� �б�
//    // �̹� ���� HSV �������� ��ȯ�ؾ� ��
//    cv::namedWindow("Image2");
//    cv::imshow("Image2", image);
//
//    cv::cvtColor(image, hsv, CV_BGR2HSV); // HSV �������� ��ȯ
//    cv::split(hsv, v); // ���� �и�
//    cv::threshold(v[1], v[1], minSat, 255, cv::THRESH_BINARY);
//    // ���� ä�� ȭ�Ҹ� ����ũ�� ����
//    // cv::namedWindow("Saturation");
//    // cv::imshow("Saturation",v[1]);
//
//    result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//    // ���� ������׷��� ������ ��������
//    // cv::namedWindow("Result Hue");
//    // cv::imshow("Result Hue",result);
//
//    cv::bitwise_and(result, v[1], result);
//    // ���� ä�� ȭ�� ���� (���� ä�� ȭ�� ���� ����)
//    // cv::namedWindow("Result Hue and");
//    // cv::imshow("Result Hue and",result);
//
//    // ���� ������׷��� ������ ��������
//    finder.setThreshold(-1.0f);
//    result = finder.find(hsv, 0.0f, 180.0f, ch, 1);
//    cv::bitwise_and(result, v[1], result);
//    // cv::namedWindow("Result Hue and raw");
//    // cv::imshow("Result Hue and raw",result);
//
//    // �ʱ� ���簢�� ���� (�ʱ� ���� �� ������ �� ��ġ)����
//    // cv::meanShift �˰����� ���ο� ������ �� ��ġ�� ���� rect ��ü�� ����
//   // cv::Rect rect(110, 260, 35, 40);
//    cv::Rect rect(100, 95, 85, 82);
//    cv::rectangle(image, rect, cv::Scalar(0, 0, 255));
//    cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER, 10, 0.01);
//    cv::meanShift(result, rect, criteria);
//    // <opencv2/video/tracking.hpp> �ʿ�
//    cv::rectangle(image, rect, cv::Scalar(0, 255, 0));
//
//    cv::namedWindow("Image 2 result");
//    cv::imshow("Image 2 result", image);
//
//    cv::waitKey(0);
//
//    return 0;
//}
//
//
///*
//
//
//���� �м�
//
//- ��ü�� Ư��ȭ�ϱ� ���� HSV �÷� ������ ���� ������Ʈ�� ��� (���� ������ ó���� ��ȯ�ؾ� ��)
//- ���� ������Ʈ�� CV_BGR2HSV �÷��׸� ����� ��� ������ ù ��° ä��.
//- 8��Ʈ ������Ʈ�μ� ���� ���� 0���� 180(cv::cvtColor�� �Բ� ���� ����� ������ Ÿ���� ���� ��ȯ�� ����)���� �ִ�.
//- ���� ������ �����Ϸ��� cv::split �Լ��� �̿��� 3ä�� HSV ������ �и��� �� ���� 1ä�� ������ ����.
//- �� ���� ������ std::vector �ν��Ͻ��� ������ ���� ������ ������ ù ��°(��, ÷�ڴ� 0) �׸��� ��.
//
//- �÷��� ���� ��Ҹ� ����ϸ� ä���� ���� ���� (������ �� ��° �׸�)�ϴ� ���� �߿�.
//- �÷��� ä���� ������ ���� ������ �Ҿ����ϰ� �ŷڰ� ������.
//- ��ǻ� ���� ä�� �÷��̱� ������ B, G, R ������Ʈ�� ���� ����, ��Ȯ�� �÷� ������ �����ϴ� �� ������� �ް� ��.
//- ��, ��������� ���� ä���� ���� �÷��� ���� ��Ҹ� ������.
//- ������׷�(minSat �Ķ���ͷ� getHueHistogram �޼ҵ忡�� �� ��谪 ���� ä���� ���� ȭ�Ҹ� ����ũ�� ����)���� ������� �ʰ� ������ ���(cv::meanShift�� ȣ���ϱ� ���� ���� ä�� �÷��� ���� ȭ�ҿ� ��� �����ϴ� ���� �κ��� �����ϴ� cv::bitwise_and �����ڸ� ���)���� ����.
//
//- ��� �̵� �˰����� Ȯ�� �Լ��� ���� �ִ�ġ�� ��ġ�� ã���� �ݺ������� ����.
//- �̸� ������ â ������ ������ ���� �߽����̳� ���� ����� ã�� ������� ����.
//- �� �˰����� ���� �߽� ��ġ�� â�� �̵��ϰ�, â ������ �߽��� �������� ������ ������ ������ ������ �ݺ�.
//
//- OpenCV�� �� ������ ���� ������ ������ ����
//- ���� �ݺ� �ִ� Ƚ���� â �߽� ���� ��ġ ��ȭ�� ���Ϸμ�, ��ġ�� �������� ������ �����ϵ��� ���.
//- �� ���� ������ cv::TermCriteria �ν��Ͻ��� ����.
//- cv::meanShift �Լ��� ���� Ƚ���� ��ȯ
//*/