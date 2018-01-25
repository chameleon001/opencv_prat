//다각형 검출 소스

//#include "opencv2/opencv.hpp"  
//#include <iostream>  
//#include <string> 
//
//using namespace cv;
//using namespace std;
//
//
////Contour 영역 내에 텍스트 쓰기 
////https://github.com/bsdnoobz/opencv-code/blob/master/shape-detect.cpp
//void setLabel(Mat& image, string str, vector<Point> contour)
//{
//    int fontface = FONT_HERSHEY_SIMPLEX;
//    double scale = 0.5;
//    int thickness = 1;
//    int baseline = 0;
//
//    Size text = getTextSize(str, fontface, scale, thickness, &baseline);
//    Rect r = boundingRect(contour);
//
//    Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
//    rectangle(image, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(200, 200, 200), CV_FILLED);
//    putText(image, str, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
//}
//
////세 점이 주어질 때 사이 각도 구하기
////http://stackoverflow.com/a/3487062
//int GetAngleABC(Point a, Point b, Point c)
//{
//    Point ab = { b.x - a.x, b.y - a.y };
//    Point cb = { b.x - c.x, b.y - c.y };
//
//    float dot = (ab.x * cb.x + ab.y * cb.y); // dot product
//    float cross = (ab.x * cb.y - ab.y * cb.x); // cross product
//
//    float alpha = atan2(cross, dot);
//
//    return (int)floor(alpha * 180.0 / CV_PI + 0.5);
//}
//
//int main(int, char**)
//{
//    Mat img_input, img_result, img_gray;
//
//    //이미지파일을 로드하여 image에 저장  
//    img_input = imread("dang1.jpg", IMREAD_COLOR);
//    if (img_input.empty())
//    {
//        cout << "Could not open or find the image" << std::endl;
//        return -1;
//    }
//
//
//    //그레이스케일 이미지로 변환  
//    cvtColor(img_input, img_gray, COLOR_BGR2GRAY);
//
//    //이진화 이미지로 변환
//    Mat binary_image;
//    threshold(img_gray, img_gray, 125, 255, THRESH_BINARY_INV | THRESH_OTSU);
//
//    //contour를 찾는다.
//    vector<vector<Point> > contours;
//    findContours(img_gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
//
//    //contour를 근사화한다.
//    vector<Point2f> approx;
//    img_result = img_input.clone();
//
//    for (size_t i = 0; i < contours.size(); i++)
//    {
//        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
//
//        if (
//            fabs(contourArea(Mat(approx))) > 100  //면적이 일정크기 이상이어야 한다. 
//                                                  //isContourConvex(Mat(approx)) //convex인지 검사한다.
//            )
//        {
//            int size = approx.size();
//
//            //Contour를 근사화한 직선을 그린다.
//            if (size % 2 == 0) {
//                line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);
//
//                for (int k = 0; k < size - 1; k++)
//                    line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);
//
//                for (int k = 0; k < size; k++)
//                    circle(img_result, approx[k], 3, Scalar(0, 0, 255));
//            }
//            else {
//                line(img_result, approx[0], approx[approx.size() - 1], Scalar(0, 255, 0), 3);
//
//                for (int k = 0; k < size - 1; k++)
//                    line(img_result, approx[k], approx[k + 1], Scalar(0, 255, 0), 3);
//
//                for (int k = 0; k < size; k++)
//                    circle(img_result, approx[k], 3, Scalar(0, 0, 255));
//            }
//
//
//            //모든 코너의 각도를 구한다.
//            vector<int> angle;
//
//            cout << "===" << size << endl;
//            for (int k = 0; k < size; k++) {
//                int ang = GetAngleABC(approx[k], approx[(k + 1) % size], approx[(k + 2) % size]);
//                cout << k << k + 1 << k + 2 << "@@" << ang << endl;
//
//                angle.push_back(ang);
//            }
//
//            sort(angle.begin(), angle.end());
//
//            int minAngle = angle.front();
//            int maxAngle = angle.back();
//            int threshold = 8;
//
//            //도형을 판정한다.
//            if (size == 3)
//                setLabel(img_result, "triangle", contours[i]);
//            else if (size == 4 && minAngle >= 90 - threshold && maxAngle <= 90 + threshold)
//                setLabel(img_result, "rectangle", contours[i]);
//            else if (size == 5 && minAngle >= 108 - threshold && maxAngle <= 108 + threshold)
//                setLabel(img_result, "pentagon", contours[i]);
//            else if (size == 6 && minAngle >= 120 - threshold && maxAngle <= 120 + threshold)
//                setLabel(img_result, "hexagon", contours[i]);
//            else setLabel(img_result, to_string(approx.size()), contours[i]);//알수 없는 경우에는 찾아낸 꼭지점 갯수를 표시
//        }
//
//    }
//
//
//    //윈도우 생성  
//    namedWindow("input", WINDOW_AUTOSIZE);
//    namedWindow("result", WINDOW_AUTOSIZE);
//
//
//    //윈도우에 출력  
//    imshow("input", img_input);
//    imshow("result", img_result);
//
//    //키보드 입력이 될때까지 대기  
//    waitKey(0);
//
//    return 0;
//}
