#include <stdio.h>
#include <stdint.h>

extern "C" {
#include <cache.h>
}

int main() {
    uint64_t ctr = cache_get_write_ctr();
    printf("cache write counter: %llu\n", (unsigned long long)ctr);
    return 0;
}
