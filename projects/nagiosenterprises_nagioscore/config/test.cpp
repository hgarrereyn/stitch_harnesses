#include <stdio.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <nagios/lib/kvvec.h>
#ifdef __cplusplus
}
#endif

int main() {
    struct kvvec *kv = kvvec_create(4);
    if (!kv) {
        printf("kvvec_create failed\n");
        return 1;
    }
    kvvec_addkv(kv, "key1", "value1");
    kvvec_addkv(kv, "key2", "value2");
    kvvec_sort(kv);
    struct kvvec_buf *buf = kvvec2buf(kv, '=', ';', 1);
    if (buf && buf->buf) {
        printf("pairs=%d; buflen=%lu; buf=", kv->kv_pairs, buf->buflen);
        fwrite(buf->buf, 1, buf->buflen, stdout);
        putchar('\n');
    } else {
        printf("pairs=%d\n", kv->kv_pairs);
    }
    kvvec_destroy(kv, 0);
    if (buf) {
        free(buf->buf);
        free(buf);
    }
    return 0;
}
