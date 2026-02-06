#include <stdio.h>
#include <string.h>
#include <ares.h>
#include <ares_version.h>

int main() {
    int rc = ares_library_init(ARES_LIB_INIT_ALL);
    if (rc != ARES_SUCCESS) {
        fprintf(stderr, "ares_library_init failed: %s\n", ares_strerror(rc));
        return 1;
    }

    ares_channel_t *channel = NULL;
    rc = ares_init(&channel);
    if (rc != ARES_SUCCESS) {
        fprintf(stderr, "ares_init failed: %s\n", ares_strerror(rc));
        ares_library_cleanup();
        return 1;
    }

    const char *verstr = ares_version(NULL);
    printf("c-ares version: %s\n", verstr ? verstr : "unknown");

    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
}
