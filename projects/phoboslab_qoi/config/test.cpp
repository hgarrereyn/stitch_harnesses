#include <stdio.h>
#include <stdlib.h>
#define QOI_NO_STDIO
#include "qoi.h"

int main() {
    // Create a tiny 2x2 RGBA checkerboard
    const int w = 2, h = 2, ch = 4;
    unsigned char pixels[w*h*ch] = {
        255,   0,   0, 255,   0, 255,   0, 255,
          0,   0, 255, 255, 255, 255,   0, 255
    };

    qoi_desc desc = { (unsigned int)w, (unsigned int)h, (unsigned char)ch, QOI_SRGB };

    int enc_size = 0;
    void *enc = qoi_encode(pixels, &desc, &enc_size);
    if (!enc || enc_size <= 0) {
        printf("encode failed\n");
        free(enc);
        return 1;
    }

    qoi_desc out_desc;
    void *dec = qoi_decode(enc, enc_size, &out_desc, ch);
    free(enc);

    if (!dec) {
        printf("decode failed\n");
        return 1;
    }

    // Verify dimensions and a couple of pixels
    if (out_desc.width != (unsigned)w || out_desc.height != (unsigned)h || out_desc.channels != ch) {
        printf("desc mismatch\n");
        free(dec);
        return 1;
    }

    unsigned char *back = (unsigned char*)dec;
    if (back[0] != 255 || back[1] != 0 || back[2] != 0 || back[3] != 255) {
        printf("pixel mismatch\n");
        free(dec);
        return 1;
    }

    printf("qoi roundtrip ok: %dx%d, %d channels, decoded %zu bytes\n", w, h, ch, (size_t)(w*h*ch));
    free(dec);
    return 0;
}
