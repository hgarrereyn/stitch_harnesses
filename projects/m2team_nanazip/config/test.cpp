#include <cstdio>
#include <cstring>
extern "C" {
#include <xxhash.h>
}

int main() {
    const char* msg = "hello, world";
    unsigned long long h64 = XXH3_64bits(msg, std::strlen(msg));
    unsigned int h32 = XXH32(msg, std::strlen(msg), 0);
    std::printf("XXH3_64bits(\"%s\") = %llu\n", msg, h64);
    std::printf("XXH32(\"%s\") = %u\n", msg, h32);
    return 0;
}
