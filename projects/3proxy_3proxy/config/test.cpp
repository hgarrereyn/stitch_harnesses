#include <cstdio>
#include <cstring>
extern "C" {
#include <proxy.h>
}

int main() {
    const unsigned char* msg = (const unsigned char*)"hello 3proxy";
    unsigned char enc[64];
    unsigned char dec[64];

    // encode
    en64(msg, enc, (int)std::strlen((const char*)msg));
    // decode
    int dlen = de64((const unsigned char*)enc, dec, 64);
    if (dlen < 0) {
        std::printf("decode error\n");
        return 1;
    }
    dec[dlen] = '\0';
    std::printf("enc=%s dec=%s\n", enc, dec);
    return 0;
}
