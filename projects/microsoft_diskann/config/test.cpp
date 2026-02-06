#include <iostream>
#include "simd_utils.h"  // ensure intrinsics macros like _MM_HINT_T0 are defined
#include "index.h"

int main() {
    double est = diskann::estimate_ram_usage(1000, 64, sizeof(float), 32);
    std::cout << "Estimated RAM: " << est << std::endl;
    return 0;
}
