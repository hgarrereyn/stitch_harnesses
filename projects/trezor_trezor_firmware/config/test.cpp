#include <cstdio>
#include <cstdint>
#include <cstring>

extern "C" {
#include "trezor-crypto/sha2.h"
}

int main() {
    const char *msg = "hello world";
    uint8_t digest[SHA256_DIGEST_LENGTH];
    sha256_Raw(reinterpret_cast<const uint8_t*>(msg), strlen(msg), digest);
    // Print first 8 bytes as hex
    const char *hex = "0123456789abcdef";
    for (int i = 0; i < 8; ++i) {
        unsigned b = digest[i];
        std::putchar(hex[(b >> 4) & 0xF]);
        std::putchar(hex[b & 0xF]);
    }
    std::putchar('\n');
    return 0;
}
