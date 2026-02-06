#include <stdio.h>
#include <string.h>
#include <md4c-html.h>

static void output_cb(const MD_CHAR* data, MD_SIZE size, void* userdata) {
    (void)userdata;
    fwrite(data, 1, size, stdout);
}

int main() {
    const char *md = "# Hello MD4C\n\n- item 1\n- item 2\n\n`code` and **bold**.\n";
    int rc = md_html((const MD_CHAR*)md, (MD_SIZE)strlen(md), output_cb, NULL, 0, 0);
    if (rc != 0) {
        fprintf(stderr, "md_html failed: %d\n", rc);
        return 1;
    }
    return 0;
}
