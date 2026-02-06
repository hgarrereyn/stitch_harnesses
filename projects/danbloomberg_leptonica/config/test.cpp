#include <leptonica/allheaders.h>
#include <cstdio>
int main() {
    const char* v = getLeptonicaVersion();
    if (v) std::printf("Leptonica version: %s\n", v);
    // Create a small image and set a pixel
    PIX *pix = pixCreate(10, 10, 8);
    if (!pix) return 1;
    pixSetPixel(pix, 5, 5, 128);
    // Compute simple statistic
    l_uint32 val = 0; pixGetPixel(pix, 5, 5, &val);
    std::printf("Pixel(5,5)=%u\n", val);
    pixDestroy(&pix);
    return 0;
}
