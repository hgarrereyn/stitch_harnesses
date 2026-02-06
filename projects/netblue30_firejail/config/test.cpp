#include <stdio.h>
#include <stdint.h>
#include "/fuzz/install/include/firejail/common.h"

int main() {
    uint32_t ip = 0, netip = 0, mask = 0;
    if (atoip("192.168.1.100", &ip) != 0) {
        puts("atoip failed");
        return 1;
    }
    if (atocidr("192.168.1.0/24", &netip, &mask) != 0) {
        puts("atocidr failed");
        return 1;
    }
    unsigned bits = mask2bits(mask);
    printf("IP: %u.%u.%u.%u, mask bits: %u\n", PRINT_IP(ip), bits);
    return 0;
}
