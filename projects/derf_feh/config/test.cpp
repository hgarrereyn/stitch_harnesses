#include <stdio.h>
#include <string.h>
#include <md5.h>

int main() {
    const char *msg = "hello world";
    md5_state_t st;
    md5_byte_t digest[16];
    md5_init(&st);
    md5_append(&st, (const md5_byte_t*)msg, (int)strlen(msg));
    md5_finish(&st, digest);

    unsigned int sum = 0;
    for (int i = 0; i < 16; i++) sum = (sum * 33) ^ digest[i];
    printf("md5 checksum hash: %u\n", sum);
    return 0;
}
