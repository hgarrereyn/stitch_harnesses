#include <iostream>
#include <functional>
#include <array>
#include "tiv_lib.h"

int main() {
    // Simple 8x4 gradient image generator
    auto get_pixel = [](int x, int y) -> unsigned long {
        unsigned char r = static_cast<unsigned char>((x * 32) & 0xFF);
        unsigned char g = static_cast<unsigned char>((y * 32) & 0xFF);
        unsigned char b = static_cast<unsigned char>((x + y) * 16 & 0xFF);
        return (static_cast<unsigned long>(r) << 16) | (static_cast<unsigned long>(g) << 8) | static_cast<unsigned long>(b);
    };

    int flags = 0; // default options
    CharData cd = findCharData(get_pixel, 0, 0, flags);

    std::cout << "Codepoint: U+" << std::hex << cd.codePoint << std::dec << "\n";
    std::cout << "FG: (" << cd.fgColor[0] << ", " << cd.fgColor[1] << ", " << cd.fgColor[2] << ")\n";
    std::cout << "BG: (" << cd.bgColor[0] << ", " << cd.bgColor[1] << ", " << cd.bgColor[2] << ")\n";

    // Success condition
    return 0;
}
