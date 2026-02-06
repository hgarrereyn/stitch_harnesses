#include <cstdio>
#include <cstring>
#include <vector>
extern "C" {
#include <zstd.h>
}

int main() {
    const char* msg = "Hello Dumper-7 ZSTD test";
    size_t msg_size = std::strlen(msg);

    size_t max_compressed = ZSTD_compressBound(msg_size);
    std::vector<char> compressed(max_compressed);

    size_t cSize = ZSTD_compress(compressed.data(), compressed.size(), msg, msg_size, 1);
    if (ZSTD_isError(cSize)) {
        std::printf("Compression error: %s\n", ZSTD_getErrorName(cSize));
        return 1;
    }
    compressed.resize(cSize);

    std::vector<char> decompressed(msg_size);
    size_t dSize = ZSTD_decompress(decompressed.data(), decompressed.size(), compressed.data(), compressed.size());
    if (ZSTD_isError(dSize)) {
        std::printf("Decompression error: %s\n", ZSTD_getErrorName(dSize));
        return 1;
    }
    std::printf("Decompressed: %.*s\n", (int)dSize, decompressed.data());
    return 0;
}
