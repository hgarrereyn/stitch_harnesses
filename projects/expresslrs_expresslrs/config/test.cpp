#include <cstdio>
#include <cstdint>
#define ICACHE_RAM_ATTR
#include "LowPassFilter.h"

int main() {
    LPF filter(3, 5);
    int32_t sum = 0;
    for (int i = 0; i < 10; ++i) {
        sum += filter.update(i * 10);
    }
    // Print something deterministic
    std::printf("sum=%d value=%d\n", (int)sum, (int)filter.value());
    return 0;
}
