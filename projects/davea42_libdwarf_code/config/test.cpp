#include <stdio.h>
#include <stdint.h>
// Per libdwarf API guidance, include dwarf.h before libdwarf.h
#include <dwarf.h>
#define LIBDWARF_STATIC 1
#include <libdwarf.h>

int main() {
    const char *ver = dwarf_package_version();
    int prev = dwarf_set_stringcheck(0); // toggle a global flag
    // Restore previous to avoid side effects (not necessary here but shows another API call)
    dwarf_set_stringcheck(prev);
    if (!ver) {
        printf("libdwarf version unknown\n");
        return 0;
    }
    printf("libdwarf package version: %s\n", ver);
    return 0;
}
