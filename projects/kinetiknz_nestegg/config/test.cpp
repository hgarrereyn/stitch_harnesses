#include <cstdio>
#include <cstdint>
#include <nestegg/nestegg.h>

int main() {
    // Minimal buffer with EBML header prefix
    unsigned char buf[4] = {0x1A, 0x45, 0xDF, 0xA3};
    int is_webm = nestegg_sniff_webm(buf, sizeof(buf));
    std::printf("sniff_webm=%d\n", is_webm);
    return 0;
}
