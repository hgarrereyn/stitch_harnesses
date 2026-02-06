#include <iostream>
#include "pag/defines.h"
#include "pag/types.h"

int main() {
    // Use a couple of inline utilities from the public API to ensure headers are usable.
    pag::Opacity a = 128, b = 200;
    pag::Opacity c = pag::OpacityConcat(a, b); // inline function
    auto p = pag::Point::Make(3.0f, 4.0f);     // inline constructor
    auto zero = pag::Point::Zero();            // inline accessor

    std::cout << "OpacityConcat(128,200)=" << (int)c
              << ", Point=(" << p.x << "," << p.y << ")"
              << ", Zero=(" << zero.x << "," << zero.y << ")" << std::endl;
    return 0;
}
