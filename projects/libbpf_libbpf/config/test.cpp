#include <stdio.h>
#include <bpf/libbpf.h>

int main() {
    const char *ver = libbpf_version_string();
    if (!ver) ver = "unknown";
    printf("libbpf version: %s\n", ver);
    // also touch a couple of simple API functions
    char buf[128];
    libbpf_strerror(LIBBPF_ERRNO__FORMAT, buf, sizeof(buf));
    printf("errstr: %s\n", buf);
    return 0;
}
