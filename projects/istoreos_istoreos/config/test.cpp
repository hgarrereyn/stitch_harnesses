#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
extern "C" {
#include <kconfig/lkc.h>
}

int main() {
    // Use some utility functions from kconfig library
    char *dup = xstrdup("hello_kconfig");
    if (!dup) return 1;
    struct gstr gs = str_new();
    str_append(&gs, dup);
    str_append(&gs, "_world");
    char *combined = str_get(&gs);
    std::cout << combined << "\n";
    // str_get returns internal buffer; do not free it separately.
    str_free(&gs);
    free(dup);
    return 0;
}
