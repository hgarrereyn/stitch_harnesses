#include <cstdio>
#include <cstring>
extern "C" {
#include <base64.h>
}

int main() {
    const char* msg = "hello, sslsplit";
    size_t encsz = 0, decsz = 0;
    char* enc = base64_enc(reinterpret_cast<const unsigned char*>(msg), std::strlen(msg), &encsz);
    if (!enc) { std::printf("enc fail\n"); return 1; }
    std::printf("enc: %s (%zu)\n", enc, encsz);
    unsigned char* dec = base64_dec(enc, encsz, &decsz);
    if (!dec) { std::printf("dec fail\n"); free(enc); return 1; }
    std::printf("dec: %s (%zu)\n", dec, decsz);
    free(enc);
    free(dec);
    return 0;
}
