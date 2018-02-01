#define HAVE_STRUCT_TIMESPEC
#include <iostream>  
#include <opencv2/core/mat.hpp>  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/imgproc.hpp>  
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <pthread.h>

using namespace cv;
using namespace std;


Mat objectHistogram;
Mat globalHistogram;
int i = 0;


void getObjectHistogram(Mat &frame, Rect object_region)
{
    const int channels[] = { 0, 1 };
    const int histSize[] = { 64, 64 };
    float range[] = { 0, 256 };
    const float *ranges[] = { range, range };

    // Histogram in object region
    Mat objectROI = frame(object_region);
    calcHist(&objectROI, 1, channels, noArray(), objectHistogram, 2, histSize, ranges, true, false);


    // A priori color distribution with cumulative histogram
    calcHist(&frame, 1, channels, noArray(), globalHistogram, 2, histSize, ranges, true, true);


    // Boosting: Divide conditional probabilities in object area by a priori probabilities of colors
    for (int y = 0; y < objectHistogram.rows; y++) {
        for (int x = 0; x < objectHistogram.cols; x++) {
            objectHistogram.at<float>(y, x) /= globalHistogram.at<float>(y, x);
        }
    }
    normalize(objectHistogram, objectHistogram, 0, 255, NORM_MINMAX);

}
void backProjection(const Mat &frame, const Mat &histogram, Mat &bp) {
    const int channels[] = { 0, 1 };
    float range[] = { 0, 256 };
    const float *ranges[] = { range, range };
    calcBackProject(&frame, 1, channels, objectHistogram, bp, ranges);
}

Mat img_input, img_hsv, img_binary, img_binary1, img_binary2, img_binary3;
Mat img_red, img_oran, img_white;
Rect prev_rect, prev_rect1, prev_rect2, prev_rect3;
Mat bp, bp1, bp2, bp3;
Rect rectroi;
Mat sub;


void* yellow(void *argumentPointer) {
    cvtColor(sub, img_oran, COLOR_BGR2HSV);
    inRange(img_oran, Scalar(4, 114, 148), Scalar(80, 234, 255), img_binary2);
    erode(img_binary2, img_binary2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(img_binary2, img_binary2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(img_binary2, img_binary2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(img_binary2, img_binary2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    if (i < 100) {
        Mat img_labels2, stats2, centroids2;
        int numOfLables2 = connectedComponentsWithStats(img_binary2, img_labels2,
            stats2, centroids2, 8, CV_32S);

        int max2 = -1, idx2 = 0;
        for (int j = 1; j < numOfLables2; j++) {
            int area = stats2.at<int>(j, CC_STAT_AREA);
            if (max2 < area)
            {
                max2 = area;
                idx2 = j;
            }
        }
        int leftb = stats2.at<int>(idx2, CC_STAT_LEFT);
        int topb = stats2.at<int>(idx2, CC_STAT_TOP);
        int widthb = stats2.at<int>(idx2, CC_STAT_WIDTH);
        int heightb = stats2.at<int>(idx2, CC_STAT_HEIGHT);


        Rect object_region2(leftb, topb, widthb, heightb);
        getObjectHistogram(img_oran, object_region2);
        prev_rect2 = object_region2;

    }
    else {
        backProjection(img_oran, objectHistogram, bp2);
        bitwise_and(bp2, img_binary2, bp2);
        RotatedRect rect1 = CamShift(bp2, prev_rect2, cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 20, 1));
        ellipse(sub, rect1, CV_RGB(255, 0, 0), 3, CV_AA);
    }
    return NULL;
}
void* white(void *argumentPointer) {

    cvtColor(sub, img_white, COLOR_BGR2HSV);
    inRange(img_white, Scalar(30, 0, 218), Scalar(100, 101, 255), img_binary3);
    erode(img_binary3, img_binary3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(img_binary3, img_binary3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(img_binary3, img_binary3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(img_binary3, img_binary3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    if (i < 100) {
        Mat img_labels3, stats3, centroids3;
        int numOfLables3 = connectedComponentsWithStats(img_binary3, img_labels3,
            stats3, centroids3, 8, CV_32S);
        int max3 = -1, idx3 = 0;
        for (int j = 1; j < numOfLables3; j++) {
            int area = stats3.at<int>(j, CC_STAT_AREA);
            if (max3 < area)
            {
                max3 = area;
                idx3 = j;
            }
        }
        int leftc = stats3.at<int>(idx3, CC_STAT_LEFT);
        int topc = stats3.at<int>(idx3, CC_STAT_TOP);
        int widthc = stats3.at<int>(idx3, CC_STAT_WIDTH);
        int heightc = stats3.at<int>(idx3, CC_STAT_HEIGHT);

        Rect object_region3(leftc, topc, widthc, heightc);
        getObjectHistogram(img_white, object_region3);
        prev_rect3 = object_region3;

    }
    else {
        backProjection(img_white, objectHistogram, bp3);
        bitwise_and(bp3, img_binary3, bp3);
        RotatedRect rect2 = CamShift(bp3, prev_rect3, cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 20, 1));
        ellipse(sub, rect2, CV_RGB(255, 0, 0), 3, CV_AA);
    }
    return NULL;
}

void *red(void *argumentPointer) {
    cvtColor(sub, img_red, COLOR_BGR2HSV);
    inRange(img_red, Scalar(170, 50, 0), Scalar(179, 255, 255), img_binary1);
    //morphological opening 작은 점들을 제거 
    erode(img_binary1, img_binary1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(img_binary1, img_binary1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    //morphological closing 영역의 구멍 메우기 
    dilate(img_binary1, img_binary1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(img_binary1, img_binary1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    if (i < 100) {
        Mat img_labels1, stats1, centroids1;
        int numOfLables1 = connectedComponentsWithStats(img_binary1, img_labels1,
            stats1, centroids1, 8, CV_32S);
        //영역박스 그리기
        int max = -1, idx = 0;
        for (int j = 1; j < numOfLables1; j++) {
            int area = stats1.at<int>(j, CC_STAT_AREA);
            if (max < area)
            {
                max = area;
                idx = j;
            }
        }
        int lefta = stats1.at<int>(idx, CC_STAT_LEFT);
        int topa = stats1.at<int>(idx, CC_STAT_TOP);
        int widtha = stats1.at<int>(idx, CC_STAT_WIDTH);
        int heighta = stats1.at<int>(idx, CC_STAT_HEIGHT);

        Rect object_region1(lefta, topa, widtha, heighta);
        getObjectHistogram(img_red, object_region1);
        prev_rect1 = object_region1;
    }
    else {
        backProjection(img_red, objectHistogram, bp1);
        bitwise_and(bp1, img_binary1, bp1);
        RotatedRect rect = CamShift(bp1, prev_rect1, cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 20, 1));
        ellipse(sub, rect, CV_RGB(255, 0, 0), 3, CV_AA);
    }
    return NULL;
}

int main()
{
    VideoCapture cap("dang1.avi");
   
    pthread_t thrd_white;
    pthread_t thrd_yellow;
    pthread_t thrd_red;
    int left;
    int top;
    int width;
    int height;

    //웹캡에서 캡처되는 이미지 크기를 320x240으로 지정  
    cap.set(CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CAP_PROP_FRAME_HEIGHT, 240);

    if (!cap.isOpened())
    {
        cout << "웹캠을 열 수 없습니다." << endl;
        return -1;
    }


    namedWindow("찾을 색범위 설정", CV_WINDOW_AUTOSIZE);

    ////트랙바에서 사용되는 변수 초기화 
    //int LowH = 170;
    //int HighH = 179;

    //int LowS = 50;
    //int HighS = 255;

    //int LowV = 0;
    //int HighV = 255;


    ////트랙바 생성 
    //cvCreateTrackbar("LowH", "찾을 색범위 설정", &LowH, 179); //Hue (0 - 179)
    //cvCreateTrackbar("HighH", "찾을 색범위 설정", &HighH, 179);

    //cvCreateTrackbar("LowS", "찾을 색범위 설정", &LowS, 255); //Saturation (0 - 255)
    //cvCreateTrackbar("HighS", "찾을 색범위 설정", &HighS, 255);

    //cvCreateTrackbar("LowV", "찾을 색범위 설정", &LowV, 255); //Value (0 - 255)
    //cvCreateTrackbar("HighV", "찾을 색범위 설정", &HighV, 255);


    //트랙바에서 사용되는 변수 초기화 
    int LowH = 101;
    int HighH = 166;

    int LowS = 150;
    int HighS = 255;

    int LowV = 0;
    int HighV = 255;


    //트랙바 생성 
    cvCreateTrackbar("LowH", "찾을 색범위 설정", &LowH, 255); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "찾을 색범위 설정", &HighH, 255);

    cvCreateTrackbar("LowS", "찾을 색범위 설정", &LowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "찾을 색범위 설정", &HighS, 255);

    cvCreateTrackbar("LowV", "찾을 색범위 설정", &LowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "찾을 색범위 설정", &HighV, 255);


    Rect trackingWindow(0, 0, 30, 30);




    while (true)
    {
        i++;

        //웹캠에서 캡처되는 속도 출력  
        //  int fps = cap.get(CAP_PROP_FPS);
        //  cout << fps << " " << i << endl;




        //카메라로부터 이미지를 가져옴 
        bool ret = cap.read(img_input);

        if (!ret)
        {
            cout << "카메라로부터 이미지를 가져올 수 없습니다." << endl;
            break;
        }


        //HSV로 변환
        cvtColor(img_input, img_hsv, COLOR_BGR2HSV);
        //cvtColor(이미지, mat_gray(바꿀거),어떻게 바꿀거):첫번째 인수로 지정된 이미지를  세번째 인수형식으로 바꾼 이미지를 두번째 인수로 돌려 준다.


        //지정한 HSV 범위를 이용하여 영상을 이진화
        //inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary);
        inRange(img_hsv, Scalar(101, 150, 0), Scalar(166, 255, 255), img_binary);


        //morphological opening 작은 점들을 제거 
        erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));


        //morphological closing 영역의 구멍 메우기 
        dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));



        // if (i < 100)
        // {

        //라벨링 
        Mat img_labels, stats, centroids;
        int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
            stats, centroids, 8, CV_32S);


        //영역박스 그리기
        int max = -1, idx = 0;
        for (int j = 1; j < numOfLables; j++) {
            int area = stats.at<int>(j, CC_STAT_AREA);
            if (max < area)
            {
                max = area;
                idx = j;
            }
        }

        left = stats.at<int>(idx, CC_STAT_LEFT);
        top = stats.at<int>(idx, CC_STAT_TOP);
        width = stats.at<int>(idx, CC_STAT_WIDTH);
        height = stats.at<int>(idx, CC_STAT_HEIGHT);


        //rectangle(img_input, Point(left, top), Point(left + width, top + height),Scalar(0, 0, 255), 1);

        Rect object_region(left, top, width, height);
        Rect rectroi1(left, top, width, height);
        sub = img_input(rectroi1);
        getObjectHistogram(img_hsv, object_region);
        prev_rect = object_region;

        ////////
        ////////
        ////////
   
        if (i < 2) {

            pthread_create(&thrd_red, NULL, red, NULL);
            pthread_create(&thrd_white, NULL, white, NULL);
            pthread_create(&thrd_yellow, NULL, yellow, NULL);
        }
  
        pthread_join(thrd_red, NULL);
        pthread_join(thrd_white, NULL);
        pthread_join(thrd_yellow, NULL);
        //cvtColor(이미지, mat_gray(바꿀거),어떻게 바꿀거):첫번째 인수로 지정된 이미지를  세번째 인수형식으로 바꾼 이미지를 두번째 인수로 돌려 준다.


        //지정한 HSV 범위를 이용하여 영상을 이진화

        //   inRange(sub, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary1);

        ////////
        /////////
        /////

        // }

        /*  else {

        backProjection(img_hsv, objectHistogram, bp);
        bitwise_and(bp, img_binary, bp);
        RotatedRect rect = CamShift(bp, prev_rect, cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 20, 1));
        ellipse(img_input, rect, CV_RGB(255, 0, 0), 3, CV_AA);

        }*/

//        imshow("이진화 영상", img_binary2);
        //     imshow("원본 영상", img_input);
        imshow("123 영상", sub);
        // imshow("레드 찾기", sub);
        //ESC키 누르면 프로그램 종료
        if (waitKey(1) == 27)
            break;
    }


    return 0;
}