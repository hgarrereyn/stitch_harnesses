#include <cstdio>
#include <cstring>
#include <tls.h>
#include <openssl/sha.h>

int main() {
    // Initialize libtls
    if (tls_init() != 0) {
        std::printf("tls_init failed\n");
        return 1;
    }
    struct tls_config *cfg = tls_config_new();
    if (!cfg) {
        std::printf("tls_config_new failed\n");
        return 1;
    }
    // Set a simple option and free
    tls_config_insecure_noverifycert(cfg);
    tls_config_free(cfg);

    // Use libcrypto SHA256 to ensure crypto library is working
    const char *msg = "hello libressl";
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, msg, std::strlen(msg));
    SHA256_Final(digest, &ctx);

    // Print first few bytes
    std::printf("SHA256: %02x%02x%02x%02x...\n", digest[0], digest[1], digest[2], digest[3]);
    return 0;
}
