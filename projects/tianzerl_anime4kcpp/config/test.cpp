#include <iostream>
#include <AC/Core.hpp>

int main() {
    using namespace ac::core;

    // Create a simple 16x16 RGB image (uint8)
    Image rgb(16, 16, 3, Image::UInt8);
    for (int y = 0; y < rgb.height(); ++y) {
        for (int x = 0; x < rgb.width(); ++x) {
            unsigned char* p = rgb.pixel(x, y);
            p[0] = static_cast<unsigned char>(x);        // R
            p[1] = static_cast<unsigned char>(y);        // G
            p[2] = static_cast<unsigned char>((x+y)%256);// B
        }
    }

    // Convert to YUV and resize
    Image yuv;
    rgb2yuv(rgb, yuv);
    Image yuv_small = resize(yuv, 0.5, 0.5);

    std::cout << "Converted and resized: "
              << yuv_small.width() << "x" << yuv_small.height()
              << ", channels=" << yuv_small.channels() << std::endl;
    return 0;
}
