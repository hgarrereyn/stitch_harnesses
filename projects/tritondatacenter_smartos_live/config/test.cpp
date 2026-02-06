#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "/fuzz/install/include/nomknod.h"

int main() {
    const char *path = "/tmp/nomknod_test_file";
    // Ensure cleanup from previous runs
    unlink(path);

    // Use the library API to create a regular file via our mknod shim
    if (mknod(path, 0644, 0) != 0) {
        perror("mknod failed");
        return 1;
    }

    // Verify the file exists and is a regular file we can open
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }
    close(fd);

    // Cleanup
    unlink(path);
    printf("nomknod library test passed\n");
    return 0;
}
