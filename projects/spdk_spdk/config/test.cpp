#include <cstdio>
#include <cinttypes>
extern "C" {
#include <spdk/version.h>
#include <spdk/util.h>
}

int main() {
    uint64_t seed = spdk_rand_xorshift64_seed();
    uint64_t val = spdk_rand_xorshift64(&seed);
#ifdef SPDK_VERSION_MAJOR
    std::printf("SPDK version: %d.%d.%d%s\n", SPDK_VERSION_MAJOR, SPDK_VERSION_MINOR, SPDK_VERSION_PATCH, SPDK_VERSION_SUFFIX);
#else
    std::printf("SPDK version header not available\n");
#endif
    std::printf("Random value: %" PRIu64 "\n", val);
    return (val == 0) ? 1 : 0;
}
