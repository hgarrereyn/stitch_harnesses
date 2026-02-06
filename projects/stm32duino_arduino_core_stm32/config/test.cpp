#include "WString.h"
#include "binary.h"
#include <cstdio>

int main() {
    // Use header-only features: F() macro and binary constants
    const __FlashStringHelper *p = F("hello");
    (void)p; // suppress unused warning
    int v = B1010; // should be 10
    // simple runtime check to avoid unused code elimination
    if (v != 10) return 1;
    // print something trivial to ensure program runs
    std::printf("ok %d\n", v);
    return 0;
}
