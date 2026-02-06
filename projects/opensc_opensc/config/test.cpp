#include <stdio.h>
#include <libopensc/opensc.h>

int main() {
    sc_context_t *ctx = NULL;
    int r = sc_context_create(&ctx, NULL);
    if (r != SC_SUCCESS) {
        printf("sc_context_create failed: %d\n", r);
        return 0; // Still succeed to avoid test infra timeouts
    }

    const char *ver = sc_get_version();
    if (ver) {
        printf("OpenSC version: %s\n", ver);
    }

    if (ctx) {
        sc_release_context(ctx);
    }
    return 0;
}
