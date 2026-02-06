#include <keystone/keystone.h>
#include <stdio.h>
#include <string.h>

int main() {
    ks_engine *ks;
    ks_err err = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
    if (err != KS_ERR_OK) {
        printf("ks_open failed: %d\n", (int)err);
        return 1;
    }

    const char *asm_str = "nop; nop; ret";
    unsigned char *enc = NULL;
    size_t enc_size = 0;
    size_t count = 0;

    int rc = ks_asm(ks, asm_str, 0, &enc, &enc_size, &count);
    if (rc != 0) {
        ks_err e = ks_errno(ks);
        printf("ks_asm failed errno=%d (%s)\n", (int)e, ks_strerror(e));
        ks_close(ks);
        return 1;
    }

    printf("Assembled %zu bytes for %zu instructions:\n", enc_size, count);
    for (size_t i = 0; i < enc_size; i++) {
        printf("%02x ", enc[i]);
    }
    printf("\n");

    ks_free(enc);
    ks_close(ks);
    return 0;
}
