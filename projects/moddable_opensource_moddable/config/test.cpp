#include <cstdio>
#include "xs.h"

int main() {
    xsSlot s{}; // simple use of a public API type
    std::printf("xsSlot size: %zu\n", sizeof(s));
    return 0;
}
