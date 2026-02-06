#include <stdio.h>
#include <sys/types.h>
#include <stddef.h>
extern "C" {
#include <vstring.h>
}

int main() {
    VSTRING *vs = vstring_alloc(16);
    vstring_sprintf(vs, "Hello %s %d", "Postfix", 42);
    VSTRING_TERMINATE(vs);
    printf("%s\n", vstring_str(vs));
    vstring_free(vs);
    return 0;
}
