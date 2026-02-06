extern "C" {
#include <mutt/lib.h>
}
#include <cstdio>
int main() {
    const char* s = "Hello, NeoMutt";
    char buf[128];
    mutt_str_copy(buf, s, sizeof(buf));
    mutt_str_upper(buf);
    size_t len = mutt_str_len(buf);
    printf("%s %zu\n", buf, len);
    return 0;
}
