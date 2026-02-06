#include <cstdio>
#include <cstdlib>
#include "brownie_capi.h"

int main() {
    const char* v = brownie_version();
    if (!v) return 1;
    std::printf("brownie_capi version: %s\n", v);
    return 0;
}
