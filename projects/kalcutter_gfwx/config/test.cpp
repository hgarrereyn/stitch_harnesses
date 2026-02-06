#include <cstdint>
#include <vector>
#include <iostream>
#include <gfwx.h>

int main() {
    using namespace GFWX;
    const int W = 8, H = 8, C = 1, L = 1;
    std::vector<uint16_t> img(W*H*C*L);
    for (int y=0;y<H;++y) for (int x=0;x<W;++x) img[y*W + x] = (uint16_t)((x + y) & 0xFF);

    Header header(W, H, L, C, 16, QualityMax, 1, BlockDefault, FilterLinear, QuantizationScalar, EncoderFast, IntentMono);

    std::vector<uint8_t> compressed(4096);
    ptrdiff_t written = compress(&img[0], header, compressed.data(), compressed.size(), nullptr, nullptr, 0);
    if (written <= 0) {
        std::cout << "Compression failed: " << (long long)written << "\n";
        return 0;
    }

    std::vector<uint16_t> out(W*H*C*L, 0);
    Header hdr2;
    ptrdiff_t st = decompress(&out[0], hdr2, compressed.data(), (size_t)written, 0, false);
    std::cout << "Status: " << (long long)st << ", out0=" << out[0] << "\n";
    return 0;
}
