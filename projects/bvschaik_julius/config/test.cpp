#include <cstdio>
extern "C" {
#include "core/time.h"
}

int main() {
    time_set_millis(12345);
    auto v = time_get_millis();
    std::printf("time=%llu\n", (unsigned long long)v);
    return 0;
}
