#include <stdio.h>
#include <wolfssl/ssl.h>
#include <wolfssl/version.h>

int main() {
    if (wolfSSL_Init() != WOLFSSL_SUCCESS) {
        printf("wolfSSL_Init failed\n");
        return 1;
    }

    printf("wolfSSL version: %s\n", LIBWOLFSSL_VERSION_STRING);

    WOLFSSL_CTX* ctx = wolfSSL_CTX_new(wolfSSLv23_client_method());
    if (!ctx) {
        printf("wolfSSL_CTX_new failed\n");
        wolfSSL_Cleanup();
        return 1;
    }
    wolfSSL_CTX_free(ctx);

    wolfSSL_Cleanup();
    return 0;
}
