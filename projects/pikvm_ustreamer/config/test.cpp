#include <cstdio>
extern "C" {
#include "base64.h"
}

int main() {
    const unsigned char data[] = { 'A', 'I', 'O', 'B', 'O', 'T' };
    char* out = nullptr;
    size_t cap = 0;
    us_base64_encode(data, sizeof(data), &out, &cap);
    if (out) {
        std::printf("base64: %s\n", out);
    }
    return 0;
}
