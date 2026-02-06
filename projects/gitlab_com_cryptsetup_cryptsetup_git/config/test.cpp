#include <stdio.h>
#include <libcryptsetup.h>

int main() {
    const char *def = crypt_get_default_type();
    if (!def) def = "(null)";

    struct crypt_device *cd = NULL;
    int r = crypt_init(&cd, NULL); // initialize context with no device
    if (r == 0 && cd) {
        const char *type = crypt_get_type(cd);
        printf("cryptsetup default type: %s\n", def);
        printf("cryptsetup context type: %s\n", type ? type : "(null)");
        crypt_free(cd);
        return 0;
    }

    printf("crypt_init failed: %d\n", r);
    return 0;
}
