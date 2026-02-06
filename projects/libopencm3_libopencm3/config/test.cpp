#include <cstdio>
#include <cstdint>
#include <libopencm3/cm3/common.h>

int main() {
    uint32_t mask = BIT0 | BIT3 | BIT7 | BIT16;
    uint32_t v = 0;
    v |= BIT0;
    v |= BIT3;
    v |= BIT7;
    v |= BIT16;
    if (v != mask) return 1;
    std::printf("mask=%u\n", (unsigned)mask);
    return 0;
}
