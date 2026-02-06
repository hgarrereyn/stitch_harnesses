#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <c-siphash.h>

int main() {
    const uint8_t seed[16] = {0};
    const char *msg = "hello, NetworkManager!";
    uint64_t h = c_siphash_hash(seed, (const uint8_t*)msg, strlen(msg));
    printf("siphash(hex): %016llx\n", (unsigned long long)h);
    return 0;
}
