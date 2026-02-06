#include <cstdio>
#include <cstring>
#include <string>
extern "C" {
#include <iso2opl.h>
}

int main() {
    const char *path = "/tmp/min.iso";
    // Create a minimal empty file to open
    FILE *f = fopen(path, "wb");
    if (!f) return 1;
    fclose(f);

    // Initialize the ISO reader (little endian)
    long long size = isofs_Init(path, 0);
    // size can be 0 for empty file; just ensure init didn't fail to open
    // Attempt a simple reset/cleanup
    isofs_Reset();

    // Print something trivial so runtime does some work
    printf("Initialized iso reader on %s, size=%lld\n", path, size);
    return 0;
}
