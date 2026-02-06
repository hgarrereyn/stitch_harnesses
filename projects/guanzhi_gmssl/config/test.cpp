#include <cstdio>
#include <cstring>
#include <gmssl/version.h>
#include <gmssl/sm3.h>

int main() {
    // Print version
    printf("GmSSL version: %s (num=%d)\n", gmssl_version_str(), gmssl_version_num());

    // Compute SM3 digest of a simple message
    const char *msg = "hello, gmssl";
    uint8_t dgst[SM3_DIGEST_SIZE];
    SM3_CTX ctx;
    sm3_init(&ctx);
    sm3_update(&ctx, reinterpret_cast<const uint8_t*>(msg), strlen(msg));
    sm3_finish(&ctx, dgst);

    // Print hex digest
    for (size_t i = 0; i < sizeof(dgst); i++) {
        printf("%02x", dgst[i]);
    }
    printf("\n");

    return 0;
}
