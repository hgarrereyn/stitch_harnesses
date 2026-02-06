#include <cstdio>
#include <cstring>
extern "C" {
#include <lz4.h>
}

int main() {
    const char* msg = "LZ4 test payload: The quick brown fox jumps over the lazy dog.\n";
    const int srcSize = (int)strlen(msg);

    const int maxDst = LZ4_compressBound(srcSize);
    char* compressed = new char[maxDst];

    int compressedSize = LZ4_compress_default(msg, compressed, srcSize, maxDst);
    if (compressedSize <= 0) {
        printf("Compression failed\n");
        delete[] compressed;
        return 1;
    }

    char* decompressed = new char[srcSize+1];
    int decompressedSize = LZ4_decompress_safe(compressed, decompressed, compressedSize, srcSize);
    if (decompressedSize < 0) {
        printf("Decompression failed\n");
        delete[] compressed;
        delete[] decompressed;
        return 1;
    }
    decompressed[decompressedSize] = '\0';

    printf("Original:    %s", msg);
    printf("Decompressed:%s", decompressed);

    int ok = (decompressedSize == srcSize && memcmp(msg, decompressed, srcSize) == 0) ? 0 : 2;

    delete[] compressed;
    delete[] decompressed;
    return ok;
}
