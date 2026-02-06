#include <cstdio>
#define STB_SPRINTF_IMPLEMENTATION
#include "stb_sprintf.h"
int main() {
    char buf[256];
    int n = stbsp_sprintf(buf, "hello %s %d", "world", 42);
    if (n <= 0) return 1;
    int sum = 0; for (int i = 0; i < n; ++i) sum += (unsigned char)buf[i];
    (void)sum;
    return 0;
}
