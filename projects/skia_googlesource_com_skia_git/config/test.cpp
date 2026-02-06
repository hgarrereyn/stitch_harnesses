#include <iostream>
#include "core/SkColor.h"

int main() {
    SkColor c = SkColorSetRGB(10, 20, 30);
    std::cout << "A:" << (int)SkColorGetA(c)
              << " R:" << (int)SkColorGetR(c)
              << " G:" << (int)SkColorGetG(c)
              << " B:" << (int)SkColorGetB(c) << "\n";
    SkScalar hsv[3] = {0};
    SkColorToHSV(c, hsv);
    std::cout << "HSV H:" << (int)hsv[0] << " S:" << (int)hsv[1] << " V:" << (int)hsv[2] << "\n";
    auto back = SkHSVToColor(hsv);
    std::cout << "Back A:" << (int)SkColorGetA(back) << "\n";
    return 0;
}
