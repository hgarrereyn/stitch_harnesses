#include <cstdio>
#include <cstddef>
#include "fileutils.h"

int main() {
    size_t sz = 0;
    void* data = mmapFile("/etc/hosts", &sz);
    if (data && sz > 0) {
        // Print first few bytes as hex
        size_t to_print = sz > 8 ? 8 : sz;
        const unsigned char* b = static_cast<const unsigned char*>(data);
        for (size_t i = 0; i < to_print; ++i) {
            std::printf("%02X", b[i]);
        }
        std::printf(" %zu\n", sz);
        unmapFile((void*)data, sz);
        return 0;
    }
    std::printf("mmap failed or empty file (size=%zu)\n", sz);
    return 0;
}
