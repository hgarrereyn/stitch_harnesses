#include <cstdio>
#include <cstddef>

extern "C" {
#include "RGFW.h"
}

int main() {
    // Use a few functions that don't require a display
    size_t sz_win = RGFW_sizeofWindow();
    size_t sz_src = RGFW_sizeofWindowSrc();
    size_t sz_surface = RGFW_sizeofSurface();
    std::printf("sizes: win=%zu src=%zu surf=%zu\n", sz_win, sz_src, sz_surface);

    unsigned char src[4] = {255, 0, 0, 255};
    unsigned char dst[4] = {0, 0, 0, 0};
    RGFW_copyImageData(dst, 1, 1, RGFW_formatRGBA8, src, RGFW_formatRGBA8);
    std::printf("dst pixel: %u %u %u %u\n", dst[0], dst[1], dst[2], dst[3]);

    void* mem = RGFW_alloc(16);
    RGFW_free(mem);
    return 0;
}
