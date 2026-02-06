#include <cstdio>
extern "C" {
#include "util/tick.h"
}

int main() {
    sc_tick t_ms = SC_TICK_FROM_MS(1500);
    sc_tick t_sec = SC_TICK_TO_SEC(t_ms);
    std::printf("tick_ms=%lld, tick_sec=%lld\n", (long long)t_ms, (long long)t_sec);
    return 0;
}
