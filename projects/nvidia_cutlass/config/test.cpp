#include <iostream>
#include <cutlass/cutlass.h>

int main() {
    // Use a small part of the public API that doesn't require CUDA at runtime
    cutlass::Status st = cutlass::Status::kSuccess;
    const char* s = cutlass::cutlassGetStatusString(st);
    std::cout << "CUTLASS status string: " << s << "\n";

    // Also exercise a simple constexpr from the header
    std::cout << "NumThreadsPerWarp: " << cutlass::NumThreadsPerWarp << "\n";
    return 0;
}
