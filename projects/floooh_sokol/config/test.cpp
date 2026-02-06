#include <cstdio>
#define SOKOL_TIME_IMPL
#include "sokol_time.h"

int main() {
    stm_setup();
    uint64_t start = stm_now();
    volatile double sink = 0.0;
    for (int i = 0; i < 100000; i++) { sink += i * 0.000001; }
    uint64_t elapsed = stm_since(start);
    double ms = stm_ms(elapsed);
    std::printf("Elapsed: %.3f ms\n", ms);
    return 0;
}
