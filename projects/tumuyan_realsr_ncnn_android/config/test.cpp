#include <cstdio>
#include <cstdint>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "/fuzz/install/include/stb_image_resize.h"

int main() {
    const int w = 2, h = 2, c = 3;
    uint8_t src[w*h*c] = {
        255,0,0,   0,255,0,
        0,0,255,   255,255,255
    };
    const int W = 4, H = 4;
    uint8_t dst[W*H*c];
    int ok = stbir_resize_uint8(src, w, h, 0, dst, W, H, 0, c);
    if (!ok) { printf("resize failed\n"); return 1; }
    long sum = 0; for (int i=0;i<W*H*c;i++) sum += dst[i];
    printf("sum=%ld\n", sum);
    return 0;
}
