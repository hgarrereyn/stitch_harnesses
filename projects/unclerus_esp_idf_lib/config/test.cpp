#include <cstdio>
#include <color.h>
#include <noise.h>

int main() {
    hsv_t hsv; hsv.h = 100; hsv.s = 200; hsv.v = 180;
    rgb_t rgb = hsv2rgb_rainbow(hsv);
    uint8_t n = inoise8_2d(100, 200);
    std::printf("RGB: %u %u %u, noise=%u\n", (unsigned)rgb.r, (unsigned)rgb.g, (unsigned)rgb.b, (unsigned)n);
    return 0;
}
