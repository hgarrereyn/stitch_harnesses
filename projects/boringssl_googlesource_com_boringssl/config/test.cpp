#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <cstdio>
#include <cstring>

int main() {
    // Initialize OpenSSL RNG and compute a SHA256 hash using both low-level and EVP API.
    unsigned char data[32];
    if (RAND_bytes(data, sizeof(data)) != 1) {
        std::puts("RAND_bytes failed");
        return 0; // Don't fail hard in test env
    }

    unsigned char digest1[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, data, sizeof(data));
    SHA256_Final(digest1, &ctx);

    // EVP one-shot digest
    unsigned char digest2[EVP_MAX_MD_SIZE];
    unsigned int len = 0;
    const EVP_MD* md = EVP_sha256();
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, nullptr);
    EVP_DigestUpdate(mdctx, data, sizeof(data));
    EVP_DigestFinal_ex(mdctx, digest2, &len);
    EVP_MD_CTX_free(mdctx);

    // Print first few bytes so program does something visible
    std::printf("SHA256[0..3] = %02x %02x %02x %02x\n", digest1[0], digest1[1], digest1[2], digest1[3]);
    std::printf("EVP len=%u first=%02x\n", len, digest2[0]);
    return 0;
}
