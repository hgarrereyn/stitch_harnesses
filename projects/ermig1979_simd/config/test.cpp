#include <iostream>
#include "Simd/SimdLib.hpp"

int main() {
    // Print basic info to ensure library is linked and CPU queried
    Simd::PrintInfo(std::cout);

    typedef Simd::View<Simd::Allocator> View;

    const size_t W = 64, H = 48;
    View a(W, H, View::Gray8);
    View b(W, H, View::Gray8);
    View c(W, H, View::Gray8);

    // Fill images with simple pattern
    for (size_t y = 0; y < H; ++y) {
        for (size_t x = 0; x < W; ++x) {
            a.data[y * a.stride + x] = static_cast<uint8_t>((x + y) & 0xFF);
            b.data[y * b.stride + x] = static_cast<uint8_t>((x * 2 + y * 3) & 0xFF);
        }
    }

    // Run a simple operation and check output is produced
    Simd::AbsDifference(a, b, c);

    uint64_t sum = 0;
    Simd::AbsDifferenceSum(a, b, sum);

    // Use result to avoid optimizing away
    std::cout << "AbsDifferenceSum: " << sum << "\n";

    // Basic check: c should be non-zero for these patterns
    size_t nonzero = 0;
    for (size_t y = 0; y < H; ++y) {
        for (size_t x = 0; x < W; ++x) {
            if (c.data[y * c.stride + x] != 0) ++nonzero;
        }
    }
    std::cout << "Nonzero pixels in diff: " << nonzero << "\n";
    return 0;
}
