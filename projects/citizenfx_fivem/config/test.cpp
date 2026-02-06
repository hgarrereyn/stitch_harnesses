#include <cstddef>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "base64.h"

int main() {
    const char* msg = "hello world";
    size_t enc_len = 0;
    char* enc = base64_encode(reinterpret_cast<const unsigned char*>(msg), std::strlen(msg), &enc_len);
    if (!enc) {
        std::printf("encode failed\n");
        return 1;
    }

    size_t dec_len = 0;
    unsigned char* dec = base64_decode(enc, enc_len, &dec_len);
    if (!dec) {
        std::printf("decode failed\n");
        return 1;
    }

    std::printf("enc_len=%zu dec_len=%zu first=%c\n", enc_len, dec_len, dec_len ? (char)dec[0] : '?');

    // free allocated buffers
    free(enc);
    free(dec);
    return 0;
}
