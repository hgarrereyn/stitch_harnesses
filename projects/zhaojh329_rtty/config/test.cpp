#include <cstdio>
#include <cstring>
extern "C" {
#include "utils.h"
}

int main() {
    const char *msg = "hello";
    char out[64];
    int n = b64_encode(msg, strlen(msg), out, sizeof(out));
    if (n < 0) return 1;
    printf("b64: %s\n", out);
    printf("size: %s\n", format_size(12345));
    return 0;
}
