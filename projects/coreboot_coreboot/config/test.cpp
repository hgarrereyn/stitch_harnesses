extern "C" {
#include <commonlib/bsd/gcd.h>
#include <commonlib/bsd/ipchksum.h>
#include <commonlib/bsd/xxhash.h>
}
#include <cstdio>
#include <cstdint>
#include <cstring>

int main() {
    uint64_t g = gcd(48, 18);
    const char *msg = "abc";
    uint32_t sum = ipchksum(msg, 3);
    uint32_t h = xxh32(msg, 3, 0);
    std::printf("g=%llu sum=%u h=%u\n", (unsigned long long)g, sum, (unsigned)h);
    return 0;
}
