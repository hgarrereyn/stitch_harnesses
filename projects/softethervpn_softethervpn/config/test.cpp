#include <stdio.h>
#include <stdint.h>

extern "C" {
#define CRYPTO_TYPES_H
#include <Mayaqua/Mayaqua.h>
}

int main() {
    int is64 = Is64() ? 1 : 0;
    printf("Mayaqua present. Is64=%d\n", is64);
    return 0;
}
