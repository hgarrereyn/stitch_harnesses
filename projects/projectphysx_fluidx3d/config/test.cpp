#include <iostream>
#include "utilities.hpp"

int main() {
    // Simple sanity uses from the library that do not require OpenCL at runtime
    float rad = radians(180.0f);
    float deg = degrees(rad);
    std::cout << "deg=" << deg << " rad=" << rad << "\n";

    // Run a tiny parallel_for to exercise threading utility
    volatile unsigned long acc = 0;
    parallel_for((uint)1000u, [&](uint n){ (void)n; acc; });

    // Use a couple of constants/macros
    std::cout << "max_int=" << max_int << " max_float=" << max_float << "\n";
    return 0;
}
