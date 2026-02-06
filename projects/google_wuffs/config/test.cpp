#include <cstdio>
#include <cstdint>

// Use Wuffs as a single-file C library. Definitions are supplied via build flags.
#include "wuffs-v0.3.c"

int main() {
    const uint8_t gif87a[] = {'G','I','F','8','7','a'}; // GIF header prefix
    wuffs_base__slice_u8 s = wuffs_base__make_slice_u8((uint8_t*)gif87a, sizeof(gif87a));
    int32_t fourcc = wuffs_base__magic_number_guess_fourcc(s, true);
    if (fourcc != WUFFS_BASE__FOURCC__GIF) {
        std::printf("Unexpected FourCC: %d\n", fourcc);
        return 1;
    }
    uint32_t r = wuffs_base__u32__rotate_left(0x12345678u, 8);
    std::printf("OK %d 0x%08X\n", (int)fourcc, r);
    return 0;
}
