#include <iostream>
#include <vector>
#include <cstring>
extern "C" {
#include <lzma.h>
}

int main() {
    const char* text = "Hello, XZ/liblzma!";
    const size_t in_size = std::strlen(text);
    const uint8_t* in = reinterpret_cast<const uint8_t*>(text);

    // Compute an upper bound for output size and allocate buffers.
    size_t out_bound = lzma_stream_buffer_bound(in_size);
    std::vector<uint8_t> compressed(out_bound);
    size_t out_pos = 0;

    lzma_ret ret = lzma_easy_buffer_encode(
        LZMA_PRESET_DEFAULT, LZMA_CHECK_CRC64, /*allocator*/nullptr,
        in, in_size,
        compressed.data(), &out_pos, compressed.size()
    );

    if (ret != LZMA_OK) {
        std::cerr << "Compression failed: " << ret << "\n";
        return 1;
    }

    size_t comp_size = out_pos;

    // Decompress using single-call decoder.
    std::vector<uint8_t> decompressed(in_size + 16);
    size_t in_pos = 0;
    size_t out_pos_dec = 0;
    uint64_t memlimit = UINT64_MAX; // no limit

    ret = lzma_stream_buffer_decode(
        &memlimit, /*flags*/0, /*allocator*/nullptr,
        compressed.data(), &in_pos, comp_size,
        decompressed.data(), &out_pos_dec, decompressed.size()
    );

    if (ret != LZMA_OK) {
        std::cerr << "Decompression failed: " << ret << "\n";
        return 1;
    }

    std::string roundtrip(reinterpret_cast<char*>(decompressed.data()), out_pos_dec);
    std::cout << "Original:  " << text << "\n";
    std::cout << "Compressed size: " << comp_size << " bytes\n";
    std::cout << "Decompressed: " << roundtrip << "\n";

    if (roundtrip != text) {
        std::cerr << "Roundtrip mismatch!\n";
        return 1;
    }

    return 0;
}
