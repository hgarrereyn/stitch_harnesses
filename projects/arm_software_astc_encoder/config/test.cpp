#include <cstdio>
#include <vector>
#include <cstdint>
#include "astcenc.h"

int main() {
    // Configure for 4x4 blocks, LDR profile, fastest preset
    astcenc_config config{};
    astcenc_error err = astcenc_config_init(ASTCENC_PRF_LDR, 4, 4, 1, ASTCENC_PRE_FASTEST, 0, &config);
    if (err != ASTCENC_SUCCESS) {
        std::printf("config_init failed: %d\n", (int)err);
        return 1;
    }

    astcenc_context* ctx = nullptr;
    err = astcenc_context_alloc(&config, 1, &ctx);
    if (err != ASTCENC_SUCCESS) {
        std::printf("context_alloc failed: %d\n", (int)err);
        return 1;
    }

    // Create a tiny 4x4 RGBA image (single 2D slice)
    const unsigned x = 4, y = 4, z = 1;
    std::vector<uint8_t> src(x * y * 4, 128);
    // simple gradient
    for (unsigned yy = 0; yy < y; ++yy) {
        for (unsigned xx = 0; xx < x; ++xx) {
            size_t idx = (yy * x + xx) * 4;
            src[idx+0] = (uint8_t)(xx * 64);
            src[idx+1] = (uint8_t)(yy * 64);
            src[idx+2] = 0;
            src[idx+3] = 255;
        }
    }

    void* slices_in[1];
    slices_in[0] = src.data();

    astcenc_image image_in{};
    image_in.dim_x = x;
    image_in.dim_y = y;
    image_in.dim_z = z;
    image_in.data_type = ASTCENC_TYPE_U8;
    image_in.data = slices_in;

    astcenc_swizzle swz{ASTCENC_SWZ_R, ASTCENC_SWZ_G, ASTCENC_SWZ_B, ASTCENC_SWZ_A};

    // For 4x4 image with 4x4 block size we get 1 block -> 16 bytes compressed
    std::vector<uint8_t> comp(16, 0);

    err = astcenc_compress_image(ctx, &image_in, &swz, comp.data(), comp.size(), 0);
    if (err != ASTCENC_SUCCESS) {
        std::printf("compress failed: %d\n", (int)err);
        astcenc_context_free(ctx);
        return 1;
    }

    // Decompress back to an output image
    std::vector<uint8_t> dst(x * y * 4, 0);
    void* slices_out[1];
    slices_out[0] = dst.data();

    astcenc_image image_out{};
    image_out.dim_x = x;
    image_out.dim_y = y;
    image_out.dim_z = z;
    image_out.data_type = ASTCENC_TYPE_U8;
    image_out.data = slices_out;

    err = astcenc_decompress_image(ctx, comp.data(), comp.size(), &image_out, &swz, 0);
    if (err != ASTCENC_SUCCESS) {
        std::printf("decompress failed: %d\n", (int)err);
        astcenc_context_free(ctx);
        return 1;
    }

    astcenc_context_free(ctx);

    // Print a checksum-ish value to ensure the code runs
    unsigned sum = 0;
    for (uint8_t v : dst) sum += v;
    std::printf("OK %u\n", sum);
    return 0;
}
