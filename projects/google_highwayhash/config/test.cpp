#include <cstdio>
#include <inttypes.h>
#include "highwayhash/highwayhash.h"

int main() {
    using namespace highwayhash;
    HH_ALIGNAS(32) const HHKey key = {1, 2, 3, 4};
    const char data[] = "hello world";
    HHResult64 result64 = 0;
    HHStateT<HH_TARGET> state(key);
    HighwayHashT(&state, data, sizeof(data)-1, &result64);
    std::printf("%016" PRIx64 "\n", (uint64_t)result64);
    return 0;
}
