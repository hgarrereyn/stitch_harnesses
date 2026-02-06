#include <stdio.h>

extern "C" {
#include "sslscan.h"
}

int main() {
    const char *name = getPrintableTLSName(TLSv1_2);
    printf("TLS name: %s\n", name ? name : "(null)");

    bs *b = NULL;
    bs_new(&b);
    unsigned char data[3] = { 'A', 'B', 'C' };
    bs_append_bytes(b, data, 3);
    printf("bs len: %zu, first byte: %c\n", bs_get_len(b), bs_get_byte(b, 0));
    bs_free(&b);
    return 0;
}
