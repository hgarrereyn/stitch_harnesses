#include <stdio.h>
#include <string.h>
extern "C" {
#include <lkc.h>
}

// Provide the missing global referenced by util.c (menu.c normally defines this)
extern "C" struct file *file_list = NULL;

int main() {
    // Test growable string API from util.c
    struct gstr gs = str_new();
    str_printf(&gs, "Hello %s %d", "OpenWrt", 2024);
    char *s = str_get(&gs);
    if (!s) return 1;
    printf("gstr: %s\n", s);

    // Test xstrdup / xmalloc wrappers
    char *dup = xstrdup("lede");
    void *buf = xmalloc(16);
    memset(buf, 0, 16);
    printf("dup: %s size=%zu\n", dup, strlen(dup));

    // Clean up
    str_free(&gs);
    free(dup);
    free(buf);
    return 0;
}
