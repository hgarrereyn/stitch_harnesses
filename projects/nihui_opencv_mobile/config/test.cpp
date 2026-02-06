#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

int main() {
    // Create a simple image and draw on it
    cv::Mat img(64, 64, CV_8UC3, cv::Scalar(10, 20, 30));
    cv::circle(img, cv::Point(32, 32), 16, cv::Scalar(200, 100, 50), -1);
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    // compute a simple checksum to ensure code runs
    int sum = (int)cv::sum(gray)[0] & 0xFF;
    return sum == -1; // always 0
}
