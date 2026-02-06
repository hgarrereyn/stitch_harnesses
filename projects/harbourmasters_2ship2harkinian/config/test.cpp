#include <stdio.h>
#include <stdint.h>
#include "attributes.h"
#include "alignment.h"

int main() {
    // Use header-only API: macros
    uint32_t v = 13;
    uint32_t a8 = ALIGN8(v);
    uint32_t a16 = ALIGN16(v);

    printf("aligned8=%u aligned16=%u\n", a8, a16);
    return 0;
}
