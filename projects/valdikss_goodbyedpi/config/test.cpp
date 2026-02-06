#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "repl_str.h"
}

int main() {
    const char *src = "hello abc world abc!";
    char *out = repl_str(src, "abc", "XYZ");
    if (!out) {
        puts("repl_str failed");
        return 1;
    }
    printf("%s\n", out);
    free(out);
    return 0;
}
