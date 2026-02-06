#include <stdio.h>
#include <string.h>
#include <picotls.h>

int main() {
    // simple exercise: use the buffer API from picotls core
    ptls_buffer_t buf;
    char smallbuf[256];
    ptls_buffer_init(&buf, smallbuf, sizeof(smallbuf));
    const char *msg = "hello picotls";
    if (ptls_buffer_reserve(&buf, strlen(msg)) != 0) {
        fprintf(stderr, "reserve failed\n");
        return 1;
    }
    memcpy(buf.base + buf.off, msg, strlen(msg));
    buf.off += strlen(msg);
    printf("buffer size=%zu, content=%.*s\n", buf.off, (int)buf.off, buf.base);
    ptls_buffer_dispose(&buf);
    return 0;
}
