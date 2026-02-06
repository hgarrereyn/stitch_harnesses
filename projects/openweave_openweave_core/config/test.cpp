#include <cstdio>
#include <cstring>
#include <cstdint>
#include <Weave/Support/Base64.h>

int main() {
    const char *msg = "hello weave";
    const uint8_t *in = reinterpret_cast<const uint8_t*>(msg);
    char enc[64] = {0};
    uint8_t dec[64] = {0};

    uint16_t enc_len = nl::Base64Encode(in, (uint16_t)strlen(msg), enc);
    uint16_t dec_len = nl::Base64Decode(enc, enc_len, dec);

    printf("Encoded: %.*s\n", enc_len, enc);
    printf("Decoded: %.*s\n", dec_len, dec);
    return 0;
}
