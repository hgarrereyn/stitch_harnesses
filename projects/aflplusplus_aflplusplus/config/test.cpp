#include <cstdio>
#include <cstdint>
#include <cstring>

// Use the header-only implementation of xxhash provided in AFL++ includes
#define XXH_INLINE_ALL
#include <afl/xxhash.h>

int main() {
    const char* msg = "hello aflplusplus";
    uint64_t h = XXH3_64bits(msg, (size_t)strlen(msg));
    std::printf("XXH3_64bits(\"%s\") = %llu\n", msg, (unsigned long long)h);
    return 0;
}
