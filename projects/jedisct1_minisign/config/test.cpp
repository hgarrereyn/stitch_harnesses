#include <cstdio>
#include <sodium.h>
#include "minisign.h"

int main() {
    if (sodium_init() < 0) {
        return 1;
    }
    std::printf("%s\n", VERSION_STRING);
    std::printf("SECRETKEYBYTES=%d PUBLICKEYBYTES=%d SIGNATUREBYTES=%d\n",
                (int)crypto_sign_SECRETKEYBYTES,
                (int)crypto_sign_PUBLICKEYBYTES,
                (int)crypto_sign_BYTES);

    KeynumPK pk{};
    KeynumSK sk{};
    (void)pk; (void)sk;
    return 0;
}
