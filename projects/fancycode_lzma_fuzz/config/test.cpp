#include <cstdio>
#include <cstring>
#include <vector>
extern "C" {
#include <LzmaLib.h>
}

int main() {
    const char* msg = "hello lzma sdk";
    size_t inSize = strlen(msg);
    std::vector<unsigned char> inBuf(msg, msg + inSize);

    // Allocate an output buffer with some extra space
    size_t outPropsSize = LZMA_PROPS_SIZE;
    unsigned char props[LZMA_PROPS_SIZE];

    size_t outSize = inSize + inSize / 16 + 64; // heuristic
    std::vector<unsigned char> outBuf(outSize);

    int res = LzmaCompress(outBuf.data(), &outSize,
                           inBuf.data(), inSize,
                           props, &outPropsSize,
                           5, // level [0..9]
                           1 << 20, // dict size
                           3, // lc
                           0, // lp
                           2, // pb
                           2, // fb
                           1 // numThreads (1 => single-threaded)
                           );

    if (res != SZ_OK) {
        std::printf("Compression failed: %d\n", res);
        return 1;
    }

    // Decompress
    size_t decSize = inSize;
    std::vector<unsigned char> decBuf(decSize);
    SizeT srcLen = outSize;
    SizeT dstLen = decSize;

    res = LzmaUncompress(decBuf.data(), &dstLen,
                         outBuf.data(), &srcLen,
                         props, outPropsSize);

    if (res != SZ_OK || dstLen != inSize || std::memcmp(decBuf.data(), inBuf.data(), inSize) != 0) {
        std::printf("Decompression failed: %d\n", res);
        return 1;
    }

    std::printf("LZMA roundtrip OK (%zu bytes)\n", inSize);
    return 0;
}
