#include <cstdio>
#include <cstring>
extern "C" {
#include "ckf.h"
}

int main() {
    // Attempt to connect to a likely closed port so it returns 0 quickly
    int fd = buildConnect("127.0.0.1", 9); // Discard port, usually closed
    if (fd > 0) {
        // If it unexpectedly connects, just close it
        // but do not include unistd.h here; we won't close to keep it simple
        printf("Connected: %d\n", fd);
    } else {
        printf("No connection (as expected)\n");
    }
    return 0;
}
