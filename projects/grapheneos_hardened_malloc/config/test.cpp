#include <cstdio>
#include <cstdint>
#include <cstdlib>
extern "C" {
#include <h_malloc.h>
}

int main() {
    void* p = h_malloc(128);
    if (!p) return 0;
    ((char*)p)[0] = 'A';
    ((char*)p)[127] = 'Z';
    size_t sz = h_malloc_object_size(p);
    std::printf("allocated upper bound size: %zu\n", sz);
    h_free(p);
    return 0;
}
