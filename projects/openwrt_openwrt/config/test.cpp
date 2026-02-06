#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lkc.h"

int main() {
    struct gstr gs = str_new();
    str_append(&gs, "Hello");
    str_printf(&gs, ", %s! %d + %d = %d", "OpenWrt", 2, 3, 5);
    char *s = str_get(&gs);
    if (!s || strstr(s, "OpenWrt") == NULL) {
        fprintf(stderr, "Unexpected string: %s\n", s ? s : "(null)");
        return 1;
    }
    const char *prefix = CONFIG_;
    if (!prefix) return 1;
    str_free(&gs);
    printf("OK: %s\n", prefix);
    return 0;
}
