#include <stdio.h>
#include <tss2/tss2_rc.h>

int main() {
    TSS2_RC rc = 0x00000100; // some TPM error code
    const char *desc = Tss2_RC_Decode(rc);
    if (!desc) desc = "(null)";
    printf("TSS2_RC 0x%08x -> %s\n", rc, desc);
    return 0;
}
