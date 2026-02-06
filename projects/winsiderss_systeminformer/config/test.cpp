#include <stdio.h>
#include <string.h>
#include <xxhash.h>

int main() {
    const char *s = "SystemInformer";
    unsigned long long h = XXH64(s, strlen(s), 0);
    printf("XXH64(\"%s\") = %llu\n", s, (unsigned long long)h);
    return 0;
}
