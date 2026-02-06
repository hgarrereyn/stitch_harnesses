#include <stdio.h>
#include <string.h>
#include <libb64/cencode.h>
#include <libb64/cdecode.h>

int main() {
    const char* input = "Hello, Arduino-Pico!";
    char encoded[128] = {0};
    char decoded[128] = {0};

    base64_encodestate enc_state; 
    base64_init_encodestate(&enc_state);
    int enc_len = base64_encode_block(input, (int)strlen(input), encoded, &enc_state);
    enc_len += base64_encode_blockend(encoded + enc_len, &enc_state);

    base64_decodestate dec_state; 
    base64_init_decodestate(&dec_state);
    int dec_len = base64_decode_block(encoded, enc_len, decoded, &dec_state);
    decoded[dec_len] = '\0';

    printf("Encoded: %s\n", encoded);
    printf("Decoded: %s\n", decoded);

    if (strcmp(input, decoded) != 0) {
        fprintf(stderr, "Round-trip failed\n");
        return 1;
    }
    return 0;
}
