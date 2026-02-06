#include <cstdio>
#include "include/core/SkColor.h"
#include "include/core/SkTypes.h"

int main() {
    // Use a simple header-only API to avoid requiring the full library link.
    SkColor c = SkColorSetARGB(255, 10, 20, 30);
    unsigned a = SkColorGetA(c);
    unsigned r = SkColorGetR(c);
    unsigned g = SkColorGetG(c);
    unsigned b = SkColorGetB(c);
    std::printf("ARGB=%u,%u,%u,%u\n", a, r, g, b);
    return 0;
}
