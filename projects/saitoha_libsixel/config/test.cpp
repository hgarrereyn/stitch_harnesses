#include <cstdio>
#include <string>
extern "C" {
#include <sixel.h>
}

static int writer(const unsigned char *data, size_t len, void *priv) {
    std::string *out = reinterpret_cast<std::string*>(priv);
    out->append(reinterpret_cast<const char*>(data), len);
    return 0; // 0 means success in libsixel writer callbacks
}

int main() {
    // Create a tiny 2x2 RGB image (red, green, blue, white)
    const int width = 2, height = 2;
    unsigned char pixels[width * height * 3] = {
        255, 0, 0,    0, 255, 0,
        0, 0, 255,    255, 255, 255
    };

    sixel_dither_t *dither = nullptr;
    sixel_output_t *output = nullptr;
    SIXELSTATUS st;

    st = sixel_dither_new(&dither, 16, nullptr);
    if (!SIXEL_SUCCEEDED(st)) return 1;
    sixel_dither_set_pixelformat(dither, SIXEL_PIXELFORMAT_RGB888);

    std::string sixel_data;
    st = sixel_output_new(&output, (sixel_write_function)writer, &sixel_data, nullptr);
    if (!SIXEL_SUCCEEDED(st)) return 2;

    st = sixel_encode(pixels, width, height, 3, dither, output);
    if (!SIXEL_SUCCEEDED(st)) return 3;

    // Print size to ensure something happened
    std::printf("Generated SIXEL bytes: %zu\n", sixel_data.size());

    sixel_output_unref(output);
    sixel_dither_unref(dither);
    return 0;
}
