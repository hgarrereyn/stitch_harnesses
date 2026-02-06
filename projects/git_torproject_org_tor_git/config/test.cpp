#include <cstdio>
#include <cstring>
extern "C" {
#include <lib/intmath/muldiv.h>
#include <lib/encoding/binascii.h>
}

int main() {
    const char *msg = "hello world";
    char out[BASE64_BUFSIZE(64)] = {0};
    int r = base64_encode(out, sizeof(out), msg, strlen(msg), 0);
    if (r < 0) {
        printf("base64_encode failed\n");
        return 1;
    }
    printf("base64('%s') = %s\n", msg, out);
    return 0;
}
