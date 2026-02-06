#include <blosc2.h>
#include <vector>
#include <cstring>
#include <iostream>

int main() {
    blosc2_init();

    const int N = 1000;
    std::vector<int32_t> src(N), dst(N);
    for (int i = 0; i < N; ++i) src[i] = i * 3 - 7;

    // Allocate compressed buffer with enough room
    size_t nbytes = src.size() * sizeof(int32_t);
    std::vector<uint8_t> cbuf(nbytes + BLOSC2_MAX_OVERHEAD);

    int csize = blosc1_compress(5, BLOSC_SHUFFLE, sizeof(int32_t), nbytes,
                                src.data(), cbuf.data(), cbuf.size());
    if (csize <= 0) {
        std::cerr << "Compression failed: " << csize << "\n";
        blosc2_destroy();
        return 1;
    }

    int dsize = blosc1_decompress(cbuf.data(), dst.data(), dst.size() * sizeof(int32_t));
    if (dsize < 0) {
        std::cerr << "Decompression failed: " << dsize << "\n";
        blosc2_destroy();
        return 1;
    }

    if (std::memcmp(src.data(), dst.data(), nbytes) != 0) {
        std::cerr << "Roundtrip mismatch" << std::endl;
        blosc2_destroy();
        return 1;
    }

    std::cout << "Blosc2 version: " << blosc2_get_version_string() << "\n";
    blosc2_destroy();
    return 0;
}
