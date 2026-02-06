#include <cstdio>
#include <cstring>
extern "C" {
#include <libssh2.h>
}

int main() {
    const char* ver = libssh2_version(0);
    if (!ver) ver = "unknown";
    // Initialize and immediately shut down to ensure basic API works
    int rc = libssh2_init(0);
    if (rc != 0) {
        std::printf("libssh2_init failed: %d\n", rc);
        return 1;
    }
    // Query a couple of simple properties (no real session; just ensure call presence)
    libssh2_exit();
    std::printf("libssh2 version: %s\n", ver);
    return 0;
}
