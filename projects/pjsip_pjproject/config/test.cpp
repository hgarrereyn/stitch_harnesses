#include <pj/string.h>
#include <stdio.h>

int main() {
    pj_str_t s; 
    pj_cstr(&s, "hello");
    printf("PJSIP test: pj_str length=%ld\n", (long)s.slen);
    return 0;
}
