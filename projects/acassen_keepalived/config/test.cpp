#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

extern "C" {
#include <utils.h>
}

int main() {
    char buf[64];
    const char* dec = format_decimal(123456789UL, 0);
    strcpy(buf, dec);

    char out[32];
    integer_to_string(42, out, sizeof(out));

    sockaddr_t sa1 = {0}, sa2 = {0};
    sa1.ss_family = AF_INET;
    sa2.ss_family = AF_INET;
    bool eq = sockstorage_equal(&sa1, &sa2);

    printf("dec=%s int=%s eq=%d\n", buf, out, (int)eq);
    return 0;
}
