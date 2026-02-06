#include <cstdio>
#include <cstdint>
extern "C" {
#include <bit_count.h>
#include <bit_scan.h>
}

int main() {
    unsigned int v1 = 0xF0F00F0u; // has many set bits
    int c = bit_count(v1);

    unsigned int v2 = 0x00000080u; // bit 7 set
    int fwd = bit_scan_forward32(v2);
    unsigned long long v3 = 0x8000000000000000ull; // highest bit set
    int rev = bit_scan_reverse64((long long)v3);

    std::printf("count=%d, fwd=%d, rev=%d\n", c, fwd, rev);
    // basic sanity checks
    if (fwd != 7) return 1;
    if (rev != 63) return 2;
    if (c <= 0) return 3;
    return 0;
}
