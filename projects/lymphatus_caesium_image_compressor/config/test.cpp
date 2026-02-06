#include <iostream>
#include <cstring>
#include "/fuzz/install/include/libcaesium.h"

int main() {
    CCSParameters params{}; // zero-initialize
    params.keep_metadata = false;
    params.jpeg_quality = 75;
    params.jpeg_chroma_subsampling = 2;
    params.jpeg_progressive = false;
    params.png_quality = 80;
    params.png_optimization_level = 4;
    params.png_force_zopfli = false;
    params.gif_quality = 80;
    params.webp_quality = 80;
    params.tiff_compression = 1;
    params.tiff_deflate_level = 6;
    params.optimize = false;
    params.width = 0;
    params.height = 0;

    const char* in = "/tmp/does_not_exist.jpg";
    const char* out = "/tmp/output.jpg";

    CCSResult res = c_compress(in, out, params);
    std::cout << "success=" << (res.success ? "true" : "false") << ", code=" << res.code << "\n";
    if (res.error_message) {
        std::cout << "error_message=" << res.error_message << "\n";
    }
    return 0;
}
