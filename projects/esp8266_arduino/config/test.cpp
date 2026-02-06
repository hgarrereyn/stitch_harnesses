#include <cstdio>
#include <cstring>
#include <cencode.h>
#include <cdecode.h>

int main() {
    const char* msg = "hello world";
    char encoded[128] = {0};
    int enc_len = base64_encode_chars(msg, (int)strlen(msg), encoded);

    char decoded[128] = {0};
    int dec_len = base64_decode_chars(encoded, enc_len, decoded);

    decoded[dec_len] = '\0';

    std::printf("orig:%s\nenc:%s\ndec:%s\n", msg, encoded, decoded);
    return 0;
}
