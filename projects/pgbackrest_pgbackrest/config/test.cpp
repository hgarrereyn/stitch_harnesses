#include <cstdio>
#include <cstdint>
#include <vector>
extern "C" {
#include "build.auto.h"
#include "common/encode.h"
}

int main() {
    const char *input = "ABC";
    size_t in_sz = 3;
    size_t out_sz = encodeToStrSize(encodingBase64, in_sz);
    std::vector<char> out(out_sz + 1, 0);
    encodeToStr(encodingBase64, reinterpret_cast<const uint8_t*>(input), in_sz, out.data());
    // Print result to ensure side effects (should be QUJD)
    std::printf("%s\n", out.data());
    return 0;
}
