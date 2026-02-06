#include <cstdio>
#include <cstdlib>
#include <advobf_shim.h>

int main() {
    const char* s = advobf_demo();
    if (!s) return 1;
    std::printf("%s\n", s);
    std::free((void*)s);
    return 0;
}
