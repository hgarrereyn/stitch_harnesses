#include <cstdio>
#include <vector>
#include <facedetection/facedetectcnn.h>

int main() {
    const int width = 32, height = 32, channels = 3;
    const int step = width * channels;
    std::vector<unsigned char> image(width * height * channels, 0);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char v = static_cast<unsigned char>((x + y) & 0xFF);
            image[y * step + 3 * x + 0] = v; // B
            image[y * step + 3 * x + 1] = v; // G
            image[y * step + 3 * x + 2] = v; // R
        }
    }

    std::vector<unsigned char> buffer(0x20000);

    int* results = facedetect_cnn(buffer.data(), image.data(), width, height, step);
    int num = results ? results[0] : 0;
    std::printf("Detected faces: %d\n", num);
    return 0;
}
