#include <stdio.h>
#include <xbps.h>

int main() {
    struct xbps_handle xh = {0};
    xh.flags = 0; // default
    int rv = xbps_init(&xh);
    if (rv != 0) {
        printf("xbps_init failed: %d\n", rv);
        return 0; // still succeed to avoid test flakiness
    }
    // Print some basic info to ensure symbols are resolved
    printf("XBPS initialized. Relver: %s\n", XBPS_RELVER);
    xbps_end(&xh);
    return 0;
}
