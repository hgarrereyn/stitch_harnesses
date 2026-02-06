#include <iostream>
#include <openMVG/image/image_container.hpp>
#include <openMVG/numeric/numeric.h>

int main() {
    openMVG::image::Image<unsigned char> img(16, 16);
    for (int y = 0; y < (int)img.Height(); ++y) {
        for (int x = 0; x < (int)img.Width(); ++x) {
            img(y, x) = static_cast<unsigned char>((x + y) % 256);
        }
    }
    unsigned long sum = 0;
    for (int y = 0; y < (int)img.Height(); ++y) {
        for (int x = 0; x < (int)img.Width(); ++x) {
            sum += img(y, x);
        }
    }
    std::cout << "Checksum: " << sum << "\n";
    return 0;
}
