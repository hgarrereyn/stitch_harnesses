#include <cstdint>
#include <cstdio>
extern "C" {
#include <hqx.h>
}

int main() {
    const int w = 2, h = 2;
    uint32_t src[w*h] = {
        0xFF0000FFu,
        0x00FF00FFu,
        0x0000FFFFu,
        0xFFFFFFFFu
    };

    hqxInit();

    const int scale = 2;
    uint32_t dst[w*h*scale*scale] = {0};
    hq2x_32(src, dst, w, h);

    unsigned long long sum = 0;
    for (size_t i = 0; i < sizeof(dst)/sizeof(dst[0]); ++i) sum += dst[i];
    std::printf("sum=%llu\n", sum);
    return 0;
}
