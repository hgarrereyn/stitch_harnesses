#include <cstdint>
#include <cstdio>
#include "pii.h"

extern "C++" int64_t pii_gettime();
extern "C++" int64_t pii_open(const char *path, uint64_t mode);
extern "C++" uint64_t pii_close(uint64_t fd);

int main() {
    int64_t t = pii_gettime();
    int64_t fd = pii_open("/tmp/chrysalisp_test.tmp", file_open_write);
    if (fd >= 0) {
        pii_close((uint64_t)fd);
    }
    std::printf("pii_gettime: %lld\n", (long long)t);
    return 0;
}
