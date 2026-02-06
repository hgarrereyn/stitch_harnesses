#include <cstdio>
#include <cstdint>
#include "lte/gateway/c/core/common/common_defs.h"
extern "C" {
#include "lte/gateway/c/core/common/backtrace.h"
}

int main() {
    // Simple encode/decode roundtrip using macros from common_defs.h
    uint8_t buf[4] = {0};
    uint16_t in = 0x1234;
    size_t offset = 0;
    ENCODE_U16(buf, in, offset);

    uint16_t out = 0;
    size_t off2 = 0;
    DECODE_U16(buf, out, off2);

    std::printf("Encoded size=%zu Decoded=0x%04x\n", offset, out);

    // Call a function from the library to ensure linkage
    display_backtrace();

    return 0;
}
