#include <cstdio>
#include <vector>
#include <string>
#include <cstdint>

#include "guetzli/jpeg_data.h"
#include "guetzli/jpeg_data_encoder.h"
#include "guetzli/jpeg_data_writer.h"

static int VecWriter(void* data, const uint8_t* buf, size_t len) {
    std::vector<uint8_t>* out = reinterpret_cast<std::vector<uint8_t>*>(data);
    out->insert(out->end(), buf, buf + len);
    return (int)len;
}

int main() {
    const int w = 16, h = 16;
    std::vector<uint8_t> rgb(3 * w * h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            rgb[3*(y*w+x)+0] = (uint8_t)(x * 16);
            rgb[3*(y*w+x)+1] = (uint8_t)(y * 16);
            rgb[3*(y*w+x)+2] = (uint8_t)((x+y) * 8);
        }
    }
    guetzli::JPEGData jpg;
    if (!guetzli::EncodeRGBToJpeg(rgb, w, h, &jpg)) {
        printf("EncodeRGBToJpeg failed\n");
        return 1;
    }
    std::vector<uint8_t> out;
    guetzli::JPEGOutput output(&VecWriter, &out);
    if (!guetzli::WriteJpeg(jpg, true, output)) {
        printf("WriteJpeg failed\n");
        return 1;
    }
    printf("Produced JPEG size: %zu bytes\n", out.size());
    return 0;
}
