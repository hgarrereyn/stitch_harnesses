#include <cstdio>
#include <cstring>
#include <rogue_shim.h>

int main() {
    const char* v = rogue_shim_version();
    int sum = rogue_shim_add(7, 35);
    if (!v || std::strlen(v) == 0) {
        std::printf("Version string missing\n");
        return 1;
    }
    std::printf("%s\n", v);
    std::printf("sum=%d\n", sum);
    return 0;
}
