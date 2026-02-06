#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include "/fuzz/install/include/DocumentDetector.h"

int main() {
    // Create a simple black image with a white rectangle simulating a document
    cv::Mat img(200, 300, CV_8UC3, cv::Scalar(0,0,0));
    cv::rectangle(img, cv::Point(50,40), cv::Point(250,160), cv::Scalar(255,255,255), -1);

    detector::DocumentDetector detector(img, 500, 0);
    auto json = detector.scanPointToJSON();
    std::cout << json << std::endl;
    return 0;
}
