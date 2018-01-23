//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//// 영상 특징을 감지할 수 있는 클래스
//class MorphoFeatures {
//private:
//    int threshold; // 이진 영상을 만들기 위한 경계값 
//                   // 코너 감지에 사용하는 구조 요소
//    cv::Mat cross;
//    cv::Mat diamond;
//    cv::Mat square;
//    cv::Mat x;
//
//    // 이진 에지 영상을 얻는다
//    void applyThreshold(cv::Mat& result) {
//        // 결과에 경계값 적용
//        if (threshold>0)
//            cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY_INV);
//    }
//
//public:
//    cv::Mat getEdges(const cv::Mat &image) {
//        cv::Mat result;
//        cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
//        // 기울기 영상 가져오기
//
//        applyThreshold(result);
//        // 이진 영상을 얻기 위한 경계값 적용
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
//    // 에지 영상 얻기
//    MorphoFeatures morpho; // 형태학 특징 인스턴스 생성
//    morpho.setThreshold(30);
//
//    cv::Mat edges; // 에지 가져오기
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
//- 형태학 필터를 이용한 코너 감지는 OpenCV로 직접 구현할 수 없기 때문에 약간 더 복잡하다.
//- 비사각형 구조 요소를 사용해야 하며, 사각형, 다이아몬드, 십자가, X 모양 같이 정의된 네 가지 구조 요소 모양이 필요.
//- 이것들은 생성자(모든 구조 요소는 간결화를 위한 5x5 차원을 갖는다)에서 이뤄진다.
//*/

//#include <iostream>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//// 영상 특징을 감지할 수 있는 클래스
//class MorphoFeatures {
//private:
//    int threshold; // 이진 영상을 만들기 위한 경계값 
//                   // 코너 감지에 사용하는 구조 요소
//    cv::Mat cross;
//    cv::Mat diamond;
//    cv::Mat square;
//    cv::Mat x;
//
//    // 이진 에지 영상을 얻는다
//    void applyThreshold(cv::Mat& result) {
//        // 결과에 경계값 적용
//        if (threshold>0)
//            cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY_INV);
//    }
//
//public:
//    cv::Mat getEdges(const cv::Mat &image) {
//        cv::Mat result;
//        cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());
//        // 기울기 영상 가져오기
//
//        applyThreshold(result);
//        // 이진 영상을 얻기 위한 경계값 적용
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
//    // 생성자 - 모든 구조 요소는 간결화를 위한 5x5 차원을 갖는다.
//    MorphoFeatures() : threshold(-1),
//        cross(5, 5, CV_8U, cv::Scalar(0)), // 십자가
//        diamond(5, 5, CV_8U, cv::Scalar(1)), // 다아이몬드
//        square(5, 5, CV_8U, cv::Scalar(1)), // 사각형
//        x(5, 5, CV_8U, cv::Scalar(0)) { // x 모양
//
//                                        // 십자가 모양을 갖는 구조 요소 생성
//        for (int i = 0; i<5; i++) {
//            cross.at<uchar>(2, i) = 1;
//            cross.at<uchar>(i, 2) = 1;
//        }
//
//        // 다이아몬드 모양을 갖는 구조 요소 생성
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
//        // x 모양을 갖는 구조 요소 생성
//        for (int i = 0; i<5; i++) {
//            x.at<uchar>(i, i) = 1;
//            x.at<uchar>(4 - i, i) = 1;
//        }
//    }
//
//    // 코너 특징을 감지할 때 결과 코너 맵을 얻기 위해
//    // 모든 구조 요소를 순서대로 적용
//    cv::Mat getCorners(const cv::Mat &image) {
//        cv::Mat result;
//        cv::dilate(image, result, cross);
//        // 십자가로 팽창 
//        cv::erode(result, result, diamond);
//        // 다이아몬드로 침식
//
//        cv::Mat result2;
//        cv::dilate(image, result2, x);
//        // X로 팽창
//
//        cv::erode(result2, result2, square);
//        // 사각형으로 침식
//        cv::absdiff(result2, result, result);
//        // 두 닫힘 영상 간의 차이값으로 코너 얻기
//        applyThreshold(result);
//        // 이진 영상을 얻기 위한 경계값 적용
//
//        return result;
//    }
//
//    // 감지 결과를 더 좋게 보여주려면 다음 메소드에서 이진 맵의
//    // 각 감지된 점을 이용해 영상 내에 원을 그려줌
//    void drawOnImage(const cv::Mat& binary, cv::Mat& image) {
//        cv::Mat_<uchar>::const_iterator it = binary.begin<uchar>();
//        cv::Mat_<uchar>::const_iterator itend = binary.end<uchar>();
//
//        for (int i = 0; it != itend; ++it, ++i) { // 각 화소별로 
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
//    // 에지 영상 얻기
//    MorphoFeatures morpho; // 형태학 특징 인스턴스 생성
//    morpho.setThreshold(-1);
//
//    // 영상에서 코너 감지
//    cv::Mat corners;
//    corners = morpho.getCorners(image); // 코너 가져오기
//    cv::morphologyEx(corners, corners, cv::MORPH_TOPHAT, cv::Mat());
//    cv::threshold(corners, corners, 40, 255, cv::THRESH_BINARY_INV);
//    cv::namedWindow("Corner Image");
//    cv::imshow("Corner Image", corners); // 코너 영상 띄워 보기
//
//    morpho.drawOnImage(corners, image); // 코너 그리기
//    cv::namedWindow("Concers on Image");
//    cv::imshow("Concers on Image", image); // 영상 내 코너 보기
//
//    cv::waitKey(0);
//
//    return 0;
//}

///*
//예제 분석
//
//- 그레이레벨 영상에 대한 형태학 연산자의 효과를 이해하는 데 도움이 되는 방법 : 해발(또는 고도)에 대응하는 그레이레벨로 된 위상적 입체감이 있는 영상을 고려하는 것.
//- 밝은 영역은 산에 대응하고, 어두운 영역은 지형 안의 계곡에 대응.
//- 에지는 어두운 화소와 밝은 화소 사이의 급격한 변화에 대응하되 가파른 절벽으로 묘사 가능.
//- 침식 연산자를 이런 지형에 적용하면 그물 결과는 특정 지역 내의 각 화소를 낮은 값으로 대치하므로, 지형의 높이를 낮추게 된다.
//- 즉, 절벽은 계곡이 확장된 '침식' 이다.
//- 팽창은 정반대의 효과를 갖는데, 절벽은 계곡 위에 있는 지형이 된다.
//- 그러나 고원(일정한 명암도를 갖는 구역)은 어느정도 변하지 않는다.
//
//- 영상의 에지(또는 절벽)을 감지하는 방법은 침식된 영상과 팽창된 영상간의 차이를 계산해 얻을 수 있다.
//- 두 변환 영상은 에지 위치에 주로 차이가 있기 때문에 그 차이로 인해 영상 에지가 두드러진다.
//- cv::MORPH_GRADIENT 인자를 입력한 cv::morphologyEx 함수로 정확하게 수행한다.
//- 큰 구조 요소는 감지된 에지의 굵기가 된다.
//- 에지 감지 연산자는 바우처 기울기(영상 기울기는 #6에서 설명)라고 한다.
//- 유사한 결과로는 간단하게 팽창한 영상에서 원 영상을 빼거나, 혹은 원 영상에서 침식한 영상을 빼서 얻을 수 있다.
//- 결과 에지는 단순히 얇게 됨.
//
//- 코너 감지는 네 가지 구조 요소를 사용하기 때문에 더 복잡.
//- 코너 연산자는 OpenCV에서 따로 구현되지 않기 때문에 여기서 여러 모양의 구조 요소를 정의하고 조합하는 방법을 보여줬다.
//- 이 아이디어는 두 개의 서로 다른 구조 요소와, 팽창과 침식에 의한 영상 닫힘에 있다.
//- 이 요소는 에지가 바로 변하는 부분을 선택하지만, 해당 효과로 인해 코너 점의 에지에 영향을 끼친다.
//- 비대칭 닫힘 연산에 대한 영향을 더욱 이해하려면 단일 흰색 사각형으로 만든 다음 영상을 사용해보자.
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
//    // 사각형 영상을 읽고 띄워 보기
//    image = cv::imread("123.jpg", 0);
//    cv::namedWindow("Square Image");
//    cv::imshow("Square Image", image);
//
//    // 십자가 모양의 구조 요소 생성
//    cv::Mat cross(5, 5, CV_8U, cv::Scalar(0));
//    for (int i = 0; i<5; i++) {
//        cross.at<uchar>(2, i) = 1;
//        cross.at<uchar>(i, 2) = 1;
//    }
//
//    // 십자가로 팽창 
//    cv::Mat result;
//    cv::dilate(image, result, cross);
//
//    // 결과 띄워 보기
//    cv::namedWindow("Dilated square with cross");
//    cv::imshow("Dilated square with cross", result);
//
//    // 다이아몬드 모양의 구조요소 생성
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
//    // 다이아몬드로 침식
//    cv::Mat result2;
//    cv::erode(result, result2, diamond);
//
//    // 결과 띄워 보기
//    cv::namedWindow("Eroded square with diamond");
//    cv::imshow("Eroded square with diamond", result2);
//
//    // 영상을 하나로 조합하기
//    cv::Mat final(100, 300, CV_8U);
//    cv::Mat window = final(cv::Rect(0, 0, 100, 100));
//    image.copyTo(window);
//    window = final(cv::Rect(100, 0, 100, 100));
//    result.copyTo(window);
//    window = final(cv::Rect(200, 0, 100, 100));
//    result2.copyTo(window);
//
//    // 조합 결과를 띄워 보기
//    cv::namedWindow("Combined");
//    cv::imshow("Combined", final);
//
//    cv::waitKey();
//
//    return 0;
//}

/*
-결과
"Square Image"
"Dilated square with cross"
"Eroded square with diamond"

- 십자가 모양의 구조 요소로 팽창했을 때 코너점을 제외하며 사각형 에지가 확장되는데, 십자가 모양이 정사각형을 건드리지 않는다. (중간 사각형)
- 팽창 이미지는 구조 요소로 침식, 즉 다이아몬드 모양을 갖는다.
- 침식은 원 위치에 대부분 에지가 있지만, 코너에 가해도 더 이상 팽창되지 않았다.
- 마지막 사각형은 모양 코너를 잃었는데, 동일한 절차로 X 모양과 사각형 모양 구조 요소를 갖고 반복한다.
- 이전 버전을 회전한 두 요소는 결과로 45도 방향에서 코너를 잡음.
- 끝으로 두 결과의 차이로 인해 코너 특징을 추출.

*/