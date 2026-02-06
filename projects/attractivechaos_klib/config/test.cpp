#include <stdio.h>
#include <stdlib.h>
#include "kstring.h"
#include "khash.h"

KHASH_MAP_INIT_INT(m32, int)

int main() {
    kstring_t s = {0,0,NULL};
    ksprintf(&s, "hello %d", 42);
    printf("len=%zu str=%s\n", (size_t)s.l, s.s ? s.s : "");
    free(s.s);

    int ret;
    khint_t k;
    khash_t(m32) *h = kh_init(m32);
    k = kh_put(m32, h, 5, &ret);
    if (ret) kh_val(h, k) = 10;
    k = kh_get(m32, h, 5);
    if (k != kh_end(h)) {
        printf("found value=%d\n", kh_val(h, k));
    }
    kh_destroy(m32, h);
    return 0;
}
