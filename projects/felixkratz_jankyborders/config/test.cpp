#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "/fuzz/install/include/hashtable.h"
}

static unsigned long int_hash(void* key) {
    // simple hash for integers
    unsigned long k = *(unsigned long*)key;
    // mix
    k ^= k >> 33;
    k *= 0xff51afd7ed558ccdULL;
    k ^= k >> 33;
    k *= 0xc4ceb9fe1a85ec53ULL;
    k ^= k >> 33;
    return k;
}

static int int_cmp(void* a, void* b) {
    return *(unsigned long*)a == *(unsigned long*)b;
}

int main() {
    table t{};
    table_init(&t, 8, int_hash, int_cmp);

    // Insert some values
    for (unsigned long i = 0; i < 10; ++i) {
        unsigned long key = i;
        unsigned long* val = (unsigned long*)malloc(sizeof(unsigned long));
        *val = i * 10;
        table_add(&t, &key, val);
    }

    // Find a couple
    for (unsigned long i = 0; i < 10; i += 3) {
        unsigned long key = i;
        unsigned long* val = (unsigned long*)table_find(&t, &key);
        if (!val) return 1;
        std::printf("key %lu -> %lu\n", i, *val);
    }

    // Remove one and ensure it is gone
    unsigned long key = 6;
    table_remove(&t, &key);
    if (table_find(&t, &key) != nullptr) return 2;

    table_clear(&t);
    table_free(&t);
    return 0;
}
