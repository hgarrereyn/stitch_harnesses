#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <zstd.h>

int main() {
    const std::string input = "Hello Zstandard! This is a small test string.";

    size_t const bound = ZSTD_compressBound(input.size());
    std::vector<unsigned char> compressed(bound);

    size_t const cSize = ZSTD_compress(compressed.data(), compressed.size(), input.data(), input.size(), /*level=*/3);
    if (ZSTD_isError(cSize)) {
        std::cerr << "Compression error: " << ZSTD_getErrorName(cSize) << "\n";
        return 1;
    }

    compressed.resize(cSize);

    std::vector<char> decompressed(input.size());
    size_t const dSize = ZSTD_decompress(decompressed.data(), decompressed.size(), compressed.data(), compressed.size());
    if (ZSTD_isError(dSize)) {
        std::cerr << "Decompression error: " << ZSTD_getErrorName(dSize) << "\n";
        return 1;
    }

    std::string output(decompressed.begin(), decompressed.end());
    if (output != input) {
        std::cerr << "Roundtrip mismatch!\n";
        return 1;
    }

    std::cout << "ZSTD roundtrip OK. Compressed " << input.size() << " bytes to " << cSize << " bytes.\n";
    return 0;
}
