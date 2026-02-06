#include <cstdio>
#include <cstring>
extern "C" {
#include "ultrajson.h"
}

int main() {
    void* d2s = nullptr;
    dconv_d2s_init(&d2s,
                   DCONV_D2S_UNIQUE_ZERO,
                   "Infinity",
                   "NaN",
                   'e',
                   DCONV_DECIMAL_IN_SHORTEST_LOW,
                   DCONV_DECIMAL_IN_SHORTEST_HIGH,
                   0,
                   0);

    char buf[64];
    int len = 0;
    int ok = dconv_d2s(d2s, 3.14159265358979323846, buf, (int)sizeof(buf), &len);
    dconv_d2s_free(&d2s);

    if (!ok || len <= 0 || len >= (int)sizeof(buf)) {
        printf("d2s failed\n");
        return 1;
    }
    buf[len] = '\0';
    printf("d2s: %s\n", buf);

    void* s2d = nullptr;
    dconv_s2d_init(&s2d, DCONV_S2D_NO_FLAGS, 0.0, 0.0, "Infinity", "NaN");
    int processed = 0;
    double value = dconv_s2d(s2d, buf, (int)strlen(buf), &processed);
    dconv_s2d_free(&s2d);

    printf("s2d: %f (processed=%d)\n", value, processed);
    return 0;
}
