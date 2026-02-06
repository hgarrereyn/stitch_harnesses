#include <iostream>
#include <cstring>
#include "zstd.h"

int main() {
    const char* src = "Hello 7-Zip ZS with Zstd!";
    size_t srcSize = strlen(src);

    size_t bound = ZSTD_compressBound(srcSize);
    std::string compressed(bound, '\0');

    size_t cSize = ZSTD_compress(compressed.data(), compressed.size(), src, srcSize, 3);
    if (ZSTD_isError(cSize)) {
        std::cout << "Compression error: " << ZSTD_getErrorName(cSize) << "\n";
        return 1;
    }

    std::string decompressed(srcSize, '\0');
    size_t dSize = ZSTD_decompress(decompressed.data(), decompressed.size(), compressed.data(), cSize);
    if (ZSTD_isError(dSize)) {
        std::cout << "Decompression error: " << ZSTD_getErrorName(dSize) << "\n";
        return 1;
    }

    std::cout << "Roundtrip: " << decompressed << "\n";
    return 0;
}
