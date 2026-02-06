#include <cstdio>
#include <cstdlib>
#include <libiberty.h>
#include <demangle.h>

int main() {
    const char* mangled = "_Z3foov"; // void foo()
    char* dem = cplus_demangle(mangled, DMGL_GNU_V3 | DMGL_PARAMS | DMGL_ANSI | DMGL_TYPES);
    if (dem) {
        printf("Demangled: %s\n", dem);
        free(dem);
    } else {
        printf("Demangling failed\n");
    }

    // Use a couple more libiberty APIs
    char *s = xstrdup("hello");
    char *t = concat(s, " ", "world", nullptr);
    printf("Concat: %s\n", t);
    free(s);
    free(t);

    return 0;
}
