#include <cstdio>
#include <cstdint>
#include <nanopb/pb_encode.h>
#include <nanopb/pb_decode.h>

int main() {
    // Encode a simple varint value using nanopb low-level API
    const uint64_t value = 123456789ULL;
    uint8_t buffer[32];

    pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    if (!pb_encode_varint(&ostream, value)) {
        std::printf("Encode failed\n");
        return 1;
    }

    size_t encoded_len = ostream.bytes_written;

    // Now decode it back
    pb_istream_t istream = pb_istream_from_buffer(buffer, encoded_len);
#ifndef PB_WITHOUT_64BIT
    uint64_t decoded = 0;
    if (!pb_decode_varint(&istream, &decoded)) {
        std::printf("Decode failed\n");
        return 1;
    }
#else
    uint32_t decoded = 0;
    if (!pb_decode_varint32(&istream, &decoded)) {
        std::printf("Decode failed\n");
        return 1;
    }
#endif

    std::printf("Encoded %llu bytes, value=%llu decoded=%llu\n", (unsigned long long)encoded_len,
                (unsigned long long)value, (unsigned long long)decoded);
    return 0;
}
