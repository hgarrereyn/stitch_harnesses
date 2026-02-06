#include <rfb/PixelFormat.h>
#include <rfb/PixelBuffer.h>
#include <core/Logger.h>
#include <cstdint>
#include <cstdio>

int main() {
    // Create two pixel formats and convert a pixel
    rfb::PixelFormat src(32, 24, false, true, 255, 255, 255, 16, 8, 0);
    rfb::PixelFormat dst(32, 24, false, true, 255, 255, 255, 0, 8, 16);

    rfb::Pixel p = src.pixelFromRGB((uint8_t)0x12, (uint8_t)0x34, (uint8_t)0x56);
    rfb::Pixel q = dst.pixelFromPixel(src, p);

    uint8_t r, g, b;
    dst.rgbFromPixel(q, &r, &g, &b);

    std::printf("Converted pixel RGB = %u %u %u\n", (unsigned)r, (unsigned)g, (unsigned)b);
    return 0;
}
