#include <cstdio>
#include <cstring>
#include "xxhash.h"

int main() {
    const char* msg = "hello xxhash";
    XXH64_hash_t h64 = XXH64(msg, strlen(msg), 0);

    // Also try a small streaming example with XXH32
    XXH32_state_t* s = XXH32_createState();
    if (!s) return 1;
    XXH32_reset(s, 0);
    XXH32_update(s, msg, strlen(msg));
    XXH32_hash_t h32 = XXH32_digest(s);
    XXH32_freeState(s);

    std::printf("XXH64=0x%016llx\n", (unsigned long long)h64);
    std::printf("XXH32=0x%08x\n", (unsigned)h32);
    return 0;
}
