#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <qs.h>
}

int main() {
    const char* query = "a=b&foo=bar&x=y";
    char* val = qs_parse_value(query, "foo");
    if (val) {
        printf("foo=%s\n", val);
        qs_free(val);
    } else {
        printf("foo not found\n");
    }

    char* s = qs_stringify("hello", "world");
    if (s) {
        printf("%s\n", s);
        qs_free(s);
    }
    return 0;
}
