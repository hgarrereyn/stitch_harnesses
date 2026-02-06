#include <cstdio>
#include <cstring>
extern "C" {
#include <tinyproxy/base64.h>
}

int main() {
    const char *input = "hello";
    char out[BASE64ENC_BYTES(5) + 1];
    std::memset(out, 0, sizeof(out));
    base64enc(out, input, 5);
    std::printf("base64(hello)=%s\n", out);
    return 0;
}
