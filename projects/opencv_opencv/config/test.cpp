#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Create a simple image and draw something
    cv::Mat img(100, 100, CV_8UC3, cv::Scalar(50, 100, 150));
    cv::circle(img, cv::Point(50, 50), 30, cv::Scalar(255, 0, 0), 2);
    cv::putText(img, "hi", cv::Point(15, 55), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,0), 1);

    // Simple blur operation
    cv::Mat blurred;
    cv::GaussianBlur(img, blurred, cv::Size(3,3), 0.5);
    std::cout << "blurred size: " << blurred.cols << "x" << blurred.rows << std::endl;

    // Compute mean as a simple check
    auto m = cv::mean(blurred);
    std::cout << "mean: (" << m[0] << "," << m[1] << "," << m[2] << ")" << std::endl;

    return 0;
}
