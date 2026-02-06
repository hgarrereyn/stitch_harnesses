#include <gc/gc.h>
#include <cstdio>
#include <cstring>

int main() {
    GC_init();
    char* p = (char*)GC_malloc(128);
    if (!p) return 1;
    std::strcpy(p, "hello from BDWGC");
    GC_gcollect(); // force a collection
    std::printf("%s | heap=%zu\n", p, (size_t)GC_get_heap_size());
    return 0;
}
