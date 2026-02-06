#include <cstdio>
#include <cstring>
extern "C" {
#include "duix_mobile.h"
}
int main() {
    const char* v = duix_version();
    if (!v || std::strlen(v) == 0) return 1;
    std::printf("Version: %s\n", v);
    return 0;
}
