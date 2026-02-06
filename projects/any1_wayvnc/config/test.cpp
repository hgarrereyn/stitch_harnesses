#include <stdio.h>
#include <stdint.h>
#include "util.h"

int main() {
    size_t a = 13, b = 8;
    size_t up = UDIV_UP(a, b);
    size_t aligned = ALIGN_UP(a, b);
    printf("UDIV_UP(%zu,%zu)=%zu, ALIGN_UP=%zu\n", a, b, up, aligned);
    // Do not call non-inline functions to avoid linking to wayvnc executable
    return 0;
}
