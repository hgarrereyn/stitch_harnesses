#include <iostream>
#include <cstring>
#include <nettle/sha2.h>

int main() {
    const char* msg = "hello nettle";
    sha256_ctx ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, strlen(msg), (const uint8_t*)msg);
    uint8_t digest[SHA256_DIGEST_SIZE];
    sha256_digest(&ctx, digest);

    unsigned sum = 0;
    for (size_t i = 0; i < sizeof(digest); i++) sum += digest[i];
    std::cout << "sha256 sum: " << sum << "\n";
    return 0;
}
