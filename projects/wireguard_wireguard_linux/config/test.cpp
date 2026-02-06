#include <cstdio>
#include <cstring>
extern "C" {
#include <linux/zalloc.h>
}

int main() {
    const char *msg = "hello from linux tools zalloc";
    size_t n = strlen(msg) + 1;
    char *buf = (char*)zalloc(n);
    if (!buf) return 1;
    memcpy(buf, msg, n);
    std::printf("%s\n", buf);
    zfree(&buf);
    return buf == nullptr ? 0 : 2;
}
