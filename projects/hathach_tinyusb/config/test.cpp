#include <stdio.h>
#include <tusb.h>

int main() {
    bool inited = tusb_inited();
    printf("TinyUSB inited: %s\n", inited ? "yes" : "no");
    printf("U16 high of 0x1234 = %u\n", (unsigned)tu_u16_high(0x1234));
    return 0;
}
