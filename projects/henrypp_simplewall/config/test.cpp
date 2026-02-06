#include <cstdio>
#include "simplewall.h"

int main() {
    const char* v = simplewall_version();
    int s = simplewall_sum(2, 3);
    std::printf("simplewall shim version: %s, sum=%d\n", v ? v : "(null)", s);
    return (v && s == 5) ? 0 : 1;
}
