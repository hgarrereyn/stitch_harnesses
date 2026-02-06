#include <iostream>
#include <cstring>
#include <lz4.h>

int main() {
    const char* msg = "hekate lz4 test data: 0123456789abcdef";
    const int srcSize = (int)std::strlen(msg) + 1; // include null terminator

    int maxDst = LZ4_compressBound(srcSize);
    std::string compressed; compressed.resize(maxDst);

    int compSize = LZ4_compress_default(msg, compressed.data(), srcSize, maxDst);
    if (compSize <= 0) {
        std::cout << "Compression failed" << std::endl;
        return 1;
    }

    std::string decompressed; decompressed.resize(srcSize);
    int decSize = LZ4_decompress_safe(compressed.data(), decompressed.data(), compSize, srcSize);
    if (decSize <= 0) {
        std::cout << "Decompression failed" << std::endl;
        return 1;
    }

    if (std::strcmp(decompressed.c_str(), msg) != 0) {
        std::cout << "Roundtrip mismatch" << std::endl;
        return 1;
    }

    std::cout << "OK: " << decompressed.c_str() << std::endl;
    return 0;
}
