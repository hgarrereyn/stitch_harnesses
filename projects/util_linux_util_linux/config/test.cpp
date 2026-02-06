#include <uuid/uuid.h>
#include <cstdio>
#include <cstring>

int main() {
    uuid_t u;
    uuid_generate(u);
    char s[37] = {0};
    uuid_unparse_lower(u, s);
    // parse back and compare
    uuid_t v;
    if (uuid_parse(s, v) != 0) {
        std::printf("parse failed\n");
        return 1;
    }
    int cmp = uuid_compare(u, v);
    std::printf("uuid: %s, cmp:%d\n", s, cmp);
    return 0;
}
