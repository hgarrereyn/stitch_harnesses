#include <iostream>
#include <vector>
#include <cstring>
extern "C" {
#include <blosc.h>
}

int main() {
    blosc_init();

    const int n = 1000;
    int32_t src[n];
    for (int i = 0; i < n; ++i) src[i] = i;

    // Output buffer must be at least nbytes + BLOSC_MAX_OVERHEAD
    size_t nbytes = sizeof(src);
    size_t destsize = nbytes + BLOSC_MAX_OVERHEAD;

    std::vector<unsigned char> dest(destsize);
    std::vector<unsigned char> back(nbytes);

    int clevel = 5; // compression level
    int doshuffle = BLOSC_SHUFFLE; // use shuffle filter
    int typesize = sizeof(src[0]);

    int csize = blosc_compress(clevel, doshuffle, typesize,
                               nbytes, src, dest.data(), dest.size());
    if (csize <= 0) {
        std::cerr << "Compression failed: " << csize << "\n";
        blosc_destroy();
        return 1;
    }

    int dsize = blosc_decompress(dest.data(), back.data(), back.size());
    if (dsize <= 0) {
        std::cerr << "Decompression failed: " << dsize << "\n";
        blosc_destroy();
        return 1;
    }

    // Verify
    if (static_cast<size_t>(dsize) != nbytes || std::memcmp(src, back.data(), nbytes) != 0) {
        std::cerr << "Roundtrip mismatch\n";
        blosc_destroy();
        return 1;
    }

    blosc_destroy();
    std::cout << "Blosc roundtrip OK. Compressed from " << nbytes << " to " << csize << " bytes.\n";
    return 0;
}
