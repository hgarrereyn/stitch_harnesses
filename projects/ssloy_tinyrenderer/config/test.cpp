#include <iostream>
#include "tgaimage.h"

int main() {
    constexpr int W = 32, H = 32;
    TGAImage img(W, H, TGAImage::RGB);
    // Draw a small diagonal line
    for (int i = 0; i < W && i < H; ++i) {
        TGAColor c; c.bgra[0]=255; c.bgra[1]=0; c.bgra[2]=0; c.bgra[3]=255; c.bytespp=3;
        img.set(i, i, c);
    }
    if (!img.write_tga_file("framebuffer.tga", true, false)) {
        std::cerr << "Failed to write image" << std::endl;
        return 1;
    }
    std::cout << "Wrote framebuffer.tga" << std::endl;
    return 0;
}
