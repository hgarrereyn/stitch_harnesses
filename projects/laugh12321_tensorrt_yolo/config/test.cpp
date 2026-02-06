#include <iostream>
#include "trtyolo.hpp"

int main() {
    // Use inline, header-only portions of the public API that do not require linking
    trtyolo::Box box(1.5f, 2.5f, 100.0f, 200.0f);
    trtyolo::RotatedBox rbox(1.0f, 2.0f, 3.0f, 4.0f, 0.785f);
    trtyolo::KeyPoint kp(10.0f, 20.0f, 0.9f);

    std::cout << box << "\n";
    std::cout << rbox << "\n";
    std::cout << kp << "\n";
    return 0;
}
