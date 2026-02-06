#include <cstdio>
#include <harfbuzz/hb.h>

int main() {
    const char* v = hb_version_string();
    if (!v) return 1;
    printf("HarfBuzz version: %s\n", v);
    return 0;
}
