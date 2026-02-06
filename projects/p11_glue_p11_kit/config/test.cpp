#include <stdio.h>
#include <stdlib.h>
#include <p11-kit/p11-kit.h>

int main() {
    // Make library quiet and query a few simple functions
    p11_kit_be_quiet();
    const char *msg = p11_kit_strerror(0); // CKR_OK
    size_t len = p11_kit_space_strlen((const unsigned char*)"Hello", 5);
    char *dup = p11_kit_space_strdup((const unsigned char*)"World", 5);

    printf("p11-kit_strerror(0) => %s\n", msg ? msg : "(null)");
    printf("space strlen => %zu, dup => %s\n", len, dup ? dup : "(null)");

    if (dup)
        free(dup);
    return 0;
}
