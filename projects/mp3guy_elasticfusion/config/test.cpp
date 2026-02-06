#include <iostream>
#include <Intrinsics.h>
#include <Resolution.h>

int main() {
    const Intrinsics& K = Intrinsics::getInstance(528.f, 528.f, 320.f, 240.f);
    const Resolution& R = Resolution::getInstance(640, 480);
    std::cout << "fx=" << K.fx() << ", fy=" << K.fy() << ", cx=" << K.cx() << ", cy=" << K.cy() << "\n";
    std::cout << "width=" << R.width() << ", height=" << R.height() << ", pixels=" << R.numPixels() << "\n";
    return 0;
}
