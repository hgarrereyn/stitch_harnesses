#include <cstdio>
extern "C" {
#include "wc.h"
}

int main() {
    const char *input = "Hello, w3m/libwc!";
    wc_ces from = WC_CES_UTF_8;
    wc_ces to = WC_CES_ISO_8859_1;
    Str out = wc_conv(input, from, to);
    if (out && out->ptr) {
        std::printf("Converted: %s\n", out->ptr);
    } else {
        std::printf("Conversion failed\n");
    }
    return 0;
}
