#include <iostream>
#define cimg_display 0
#include "CImg.h"

int main() {
    using namespace cimg_library;
    // Create a simple RGB image and draw something
    CImg<unsigned char> img(64, 64, 1, 3, 0);
    unsigned char red[3] = {255, 0, 0};
    unsigned char green[3] = {0, 255, 0};
    img.draw_circle(32, 32, 20, red);
    img.draw_line(0, 0, 63, 63, green);
    // Compute a simple statistic
    double mean_val = img.mean();
    std::cout << "Mean: " << mean_val << "\n";
    return 0;
}
