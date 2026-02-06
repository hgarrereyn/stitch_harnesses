#include <stdio.h>
#include <string.h>
extern "C" {
#include <lib/base64.h>
}

int main() {
    const char *msg = "hello frr";
    char enc[128];
    char dec[128];
    struct base64_encodestate es; 
    struct base64_decodestate ds; 
    base64_init_encodestate(&es);
    int n1 = base64_encode_block(msg, (int)strlen(msg), enc, &es);
    int n2 = base64_encode_blockend(enc + n1, &es);
    int enclen = n1 + n2;

    base64_init_decodestate(&ds);
    int declen = base64_decode_block(enc, enclen, dec, &ds);
    dec[declen] = '\0';

    printf("enc:%.*s dec:%s\n", enclen, enc, dec);
    return 0;
}
