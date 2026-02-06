#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
extern "C" {
#include <zlib.h>
}

int main() {
    const char* input = "hello zlib - quick check";
    uLong srcLen = (uLong)strlen(input) + 1; // include NUL

    // Allocate destination buffer with recommended size
    uLong bound = compressBound(srcLen);
    std::vector<unsigned char> compressed(bound);
    uLongf compLen = bound;

    int ret = compress2(compressed.data(), &compLen, (const Bytef*)input, srcLen, Z_BEST_SPEED);
    if (ret != Z_OK) {
        std::printf("compress2 failed: %d\n", ret);
        return 1;
    }

    std::vector<unsigned char> decompressed(srcLen);
    uLongf decompLen = srcLen;
    ret = uncompress(decompressed.data(), &decompLen, compressed.data(), compLen);
    if (ret != Z_OK) {
        std::printf("uncompress failed: %d\n", ret);
        return 1;
    }

    std::string out((char*)decompressed.data());
    std::printf("Round-trip: %s\n", out.c_str());
    return out == input ? 0 : 2;
}
