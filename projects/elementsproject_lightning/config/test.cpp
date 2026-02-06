#include <stdio.h>
#include <string.h>
#include <stdint.h>
extern "C" {
#include <common/bech32.h>
}

int main() {
    // Example: encode a segwit v0 P2WPKH program for hrp "bc"
    const char *hrp = "bc"; // mainnet
    uint8_t prog[20] = {0};
    for (int i = 0; i < 20; ++i) prog[i] = (uint8_t)i; // dummy program

    char addr[128];
    if (!segwit_addr_encode(addr, hrp, 0, prog, sizeof(prog))) {
        printf("encode failed\n");
        return 1;
    }

    int ver = -1; uint8_t outprog[40]; size_t outlen = 0; char out_hrp[128];
    if (!segwit_addr_decode(&ver, outprog, &outlen, hrp, addr)) {
        printf("decode failed\n");
        return 1;
    }

    printf("addr=%s ver=%d len=%zu first=%u\n", addr, ver, outlen, (unsigned)outprog[0]);
    return 0;
}
