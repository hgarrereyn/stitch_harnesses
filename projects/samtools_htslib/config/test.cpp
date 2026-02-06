#include <stdio.h>
#include <string.h>
#include "htslib/bgzf.h"

int main() {
    const char *out = "/dev/null";
    BGZF *fp = bgzf_open(out, "w");
    if (!fp) {
        fprintf(stderr, "Failed to open %s for BGZF write\n", out);
        return 1;
    }
    const char *msg = "hello htslib\n";
    if (bgzf_write(fp, msg, (int)strlen(msg)) < 0) {
        fprintf(stderr, "bgzf_write failed\n");
        bgzf_close(fp);
        return 1;
    }
    if (bgzf_close(fp) != 0) {
        fprintf(stderr, "bgzf_close failed\n");
        return 1;
    }
    return 0;
}
