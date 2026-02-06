#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
extern "C" {
#include <gif_lib.h>
}

int main() {
    // Create a small 4x4 RGB image with a gradient
    const unsigned int W = 4, H = 4;
    std::vector<unsigned char> r(W*H), g(W*H), b(W*H);
    for (unsigned int y = 0; y < H; ++y) {
        for (unsigned int x = 0; x < W; ++x) {
            size_t idx = y*W + x;
            r[idx] = (unsigned char)(x*64);
            g[idx] = (unsigned char)(y*64);
            b[idx] = (unsigned char)(idx*4);
        }
    }
    int cmapSize = 256; // requested palette size
    std::vector<GifColorType> palette(cmapSize);
    std::vector<unsigned char> indexed(W*H);

    int rc = GifQuantizeBuffer(W, H, &cmapSize, r.data(), g.data(), b.data(), indexed.data(), palette.data());
    if (rc != GIF_OK) {
        std::printf("GifQuantizeBuffer failed: %d\n", rc);
        return 1;
    }
    std::printf("Quantized %ux%u to %d colors. First pixel index=%u RGB=(%u,%u,%u)\n",
                W, H, cmapSize, (unsigned)indexed[0], (unsigned)palette[ indexed[0] ].Red,
                (unsigned)palette[ indexed[0] ].Green, (unsigned)palette[ indexed[0] ].Blue);
    return 0;
}
