#include <cstdio>
#include <criu/criu.h>

int main() {
    if (criu_init_opts() != 0) {
        std::puts("criu_init_opts failed");
        return 1;
    }
    // Set some benign options that don't require a CRIU service
    criu_set_log_level(CRIU_LOG_ERROR);
    criu_free_opts();

    // Print compile-time version information from version.h
    std::printf("libcriu present, version %s (major=%d minor=%d)\n",
                CRIU_VERSION,
                CRIU_VERSION_MAJOR,
                CRIU_VERSION_MINOR);
    return 0;
}
