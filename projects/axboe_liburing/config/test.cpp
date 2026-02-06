#include <stdio.h>
#include <liburing.h>

int main() {
    int maj = io_uring_major_version();
    int min = io_uring_minor_version();
    bool newer = io_uring_check_version(maj, min + 1);
    printf("liburing version: %d.%d, newer? %s\n", maj, min, newer ? "yes" : "no");
    return 0;
}
