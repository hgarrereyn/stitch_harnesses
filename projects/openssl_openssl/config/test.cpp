#include <openssl/evp.h>
#include <openssl/err.h>
#include <cstring>
#include <cstdio>

int main() {
    // Initialize OpenSSL (3.x lazy init is fine, but load default provider for safety)
    // In OpenSSL 3.x, algorithms are available by default through default provider.
    const char *msg = "hello world";
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int mdlen = 0;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Failed to alloc ctx\n");
        return 1;
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1) {
        fprintf(stderr, "DigestInit failed: %lu\n", ERR_get_error());
        EVP_MD_CTX_free(ctx);
        return 1;
    }
    if (EVP_DigestUpdate(ctx, msg, std::strlen(msg)) != 1) {
        fprintf(stderr, "DigestUpdate failed: %lu\n", ERR_get_error());
        EVP_MD_CTX_free(ctx);
        return 1;
    }
    if (EVP_DigestFinal_ex(ctx, md, &mdlen) != 1) {
        fprintf(stderr, "DigestFinal failed: %lu\n", ERR_get_error());
        EVP_MD_CTX_free(ctx);
        return 1;
    }
    EVP_MD_CTX_free(ctx);

    // Print first 4 bytes to ensure it ran
    printf("SHA256('%s') starts with: %02x%02x%02x%02x (len=%u)\n", msg, md[0], md[1], md[2], md[3], mdlen);
    return 0;
}
