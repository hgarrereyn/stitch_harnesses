#include <iostream>
#include <vector>
#include <cstring>
extern "C" {
#include <nanosvg/nanosvg.h>
#include <nanosvg/nanosvgrast.h>
}

int main() {
    const char* svg_ro = "<svg xmlns='http://www.w3.org/2000/svg' width='16' height='16' viewBox='0 0 16 16'>"
                         "<rect x='1' y='1' width='14' height='14' fill='red'/></svg>";
    // Make a writable copy because nsvgParse may modify the input buffer.
    std::vector<char> svg(strlen(svg_ro) + 1);
    std::memcpy(svg.data(), svg_ro, svg.size());

    NSVGimage* image = nsvgParse(svg.data(), "px", 96.0f);
    if (!image) return 1;

    int w = (int)image->width;
    int h = (int)image->height;
    if (w <= 0 || h <= 0) { w = 16; h = 16; }

    NSVGrasterizer* rast = nsvgCreateRasterizer();
    if (!rast) { nsvgDelete(image); return 1; }

    std::vector<unsigned char> buffer((size_t)w * (size_t)h * 4u, 0);
    nsvgRasterize(rast, image, 0.0f, 0.0f, 1.0f, buffer.data(), w, h, w * 4);

    size_t nonzero = 0;
    for (size_t i = 0; i < buffer.size(); i += 4) if (buffer[i+3] != 0) ++nonzero;

    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);
    std::cout << "OK nonzero=" << nonzero << "\n";
    return nonzero ? 0 : 1;
}
