#include <cstdio>
#include <cstdint>
#include <cstring>
extern "C" {
#include <sha1.h>
}

int main() {
    const char* msg = "hello world";
    SHA1_CTX ctx;
    uint8_t digest[SHA1_DIGEST_LENGTH];

    SHA1Init(&ctx);
    SHA1Update(&ctx, reinterpret_cast<const uint8_t*>(msg), strlen(msg));
    SHA1Final(digest, &ctx);

    // Print first 5 bytes as a quick sanity check
    for (int i = 0; i < 5; ++i) {
        std::printf("%02x", digest[i]);
    }
    std::printf("\n");
    return 0;
}
