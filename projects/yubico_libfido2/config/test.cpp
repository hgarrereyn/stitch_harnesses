#include <cstdio>
#include <fido.h>
#include <fido/err.h>

int main() {
    // Initialize the library (no flags)
    fido_init(0);

    // Create and free a few opaque objects to ensure symbols are linked
    fido_cbor_info_t *ci = fido_cbor_info_new();
    fido_assert_t *as = fido_assert_new();
    fido_cred_t *cr = fido_cred_new();
    fido_dev_t *dv = fido_dev_new();

    // Use a function from err.h
    const char *ok = fido_strerr(FIDO_OK);
    if (ok)
        std::printf("fido_strerr(FIDO_OK) = %s\n", ok);

    fido_cbor_info_free(&ci);
    fido_assert_free(&as);
    fido_cred_free(&cr);
    fido_dev_free(&dv);

    return 0;
}
