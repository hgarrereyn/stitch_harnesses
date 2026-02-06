#include <stdint.h>
#include <glib.h>
#include <qemu/compiler.h>
#include <qemu/bswap.h>
#include <cstdio>

int main() {
    uint32_t v = 0x12345678u;
    uint32_t r = bswap32(v);
    std::printf("bswap32(%08x) = %08x\n", v, r);
    uint32_t v24 = 0x00a1b2c3u;
    uint32_t r24 = bswap24(v24);
    std::printf("bswap24(%06x) = %06x\n", v24 & 0x00ffffffu, r24 & 0x00ffffffu);
    return 0;
}
