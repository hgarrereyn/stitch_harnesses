#include <ImfRgbaFile.h>
#include <ImfArray.h>
#include <Iex.h>
#include <IlmThread.h>
#include <iostream>

using namespace OPENEXR_IMF_NAMESPACE;

int main() {
    try {
        int width = 4, height = 4;
        Array2D<Rgba> pixels(height, width);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float c = (x + y) % 2 ? 0.2f : 0.8f;
                pixels[y][x] = Rgba(c, c, c);
            }
        }
        RgbaOutputFile file("/tmp/minitest.exr", width, height, WRITE_RGBA);
        file.setFrameBuffer(&pixels[0][0], 1, width);
        file.writePixels(height);
        std::cout << "Wrote /tmp/minitest.exr\n";
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
