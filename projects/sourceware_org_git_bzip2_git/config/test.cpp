#include <cstdio>
#include <cstring>
#include <string>
extern "C" {
#include <bzlib.h>
}

int main() {
    const std::string input = "The quick brown fox jumps over the lazy dog.\n";

    unsigned int compLen = input.size() * 2 + 600; // per docs: allow extra space
    std::string compressed;
    compressed.resize(compLen);

    int rc = BZ2_bzBuffToBuffCompress(&compressed[0], &compLen,
                                      const_cast<char*>(input.data()), (unsigned int)input.size(),
                                      9, 0, 30);
    if (rc != BZ_OK) {
        std::printf("Compression failed: %d\n", rc);
        return 1;
    }
    compressed.resize(compLen);

    unsigned int decompLen = input.size() * 3 + 10;
    std::string decompressed;
    decompressed.resize(decompLen);

    rc = BZ2_bzBuffToBuffDecompress(&decompressed[0], &decompLen,
                                    &compressed[0], (unsigned int)compressed.size(),
                                    0, 0);
    if (rc != BZ_OK) {
        std::printf("Decompression failed: %d\n", rc);
        return 1;
    }
    decompressed.resize(decompLen);

    std::printf("Original: %s\n", input.c_str());
    std::printf("Round-trip ok: %s\n", (decompressed == input) ? "yes" : "no");
    return decompressed == input ? 0 : 1;
}
