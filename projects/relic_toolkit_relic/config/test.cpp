#include <cstdio>
#include <relic/relic.h>

int main() {
    if (core_init() != RLC_OK) {
        return 1;
    }
    bn_t a, b, c;
    bn_null(a); bn_null(b); bn_null(c);
    bn_new(a); bn_new(b); bn_new(c);

    bn_set_dig(a, 123);
    bn_set_dig(b, 456);
    bn_add(c, a, b);

    int size = bn_size_str(c, 10);
    char *buf = (char*)malloc(size);
    bn_write_str(buf, size, c, 10);
    printf("%s\n", buf);
    free(buf);

    bn_free(a); bn_free(b); bn_free(c);
    core_clean();
    return 0;
}
