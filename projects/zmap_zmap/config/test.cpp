#include <stdio.h>
#include <stdint.h>
extern "C" {
#include "util.h"
}

int main() {
    char buf[64];
    number_string(1234567, buf, sizeof(buf));
    printf("number_string: %s\n", buf);

    char tbuf[64];
    time_string(3661, 0, tbuf, sizeof(tbuf));
    printf("time_string: %s\n", tbuf);

    printf("max_int(3,7)=%d min_int(3,7)=%d\n", max_int(3,7), min_int(3,7));

    double t1 = steady_now();
    for (volatile int i=0;i<100000;i++); // busy loop
    double t2 = steady_now();
    printf("steady_now delta: %.6f\n", t2 - t1);
    return 0;
}
