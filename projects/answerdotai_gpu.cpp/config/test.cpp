#include <iostream>
#include "gpu.hpp"

int main() {
    using namespace gpu;

    // Pure CPU-side usage of the API (no GPU context required)
    Shape s{2, 3, 4};
    size_t elems = size(s);

    // Test simple string/template utilities and KernelCode substitution
    const char* wgsl = R"(
        @compute @workgroup_size({{workgroupSize}})
        fn main() { }
    )";
    KernelCode kc{std::string(wgsl), 64, kf32};

    std::cout << "elems=" << elems << " workgroup_x=" << kc.workgroupSize[0] << "\n";
    // Should print: elems=24 workgroup_x=64
    return (elems == 24 && kc.workgroupSize[0] == 64) ? 0 : 1;
}
