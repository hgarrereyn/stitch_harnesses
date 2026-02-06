extern "C" {
#include <fcyc.h>
}

static void dummy(long int* params) {
    volatile long sum = 0;
    for (long i = 0; i < 1000; i++) sum += i;
    (void)params;
}

int main() {
    long int p[1] = {0};
    double c = fcyc(dummy, p);
    (void)c;
    return 0;
}
