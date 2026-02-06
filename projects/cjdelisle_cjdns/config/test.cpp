#include <stdio.h>
#define restrict
extern "C" {
#include "memory/Allocator.h"
#include "benc/Dict.h"
#include "benc/String.h"
}

int main() {
    struct Allocator* alloc = Allocator_new(1UL<<20);
    Dict* d = Dict_new(alloc);
    String* key = String_new("hello", alloc);
    String* val = String_new("world", alloc);
    Dict_putString(d, key, val, alloc);
    String* s = Dict_getString(d, key);
    if (s) {
        printf("%.*s\n", (int)s->len, s->bytes);
    } else {
        printf("not found\n");
    }
    Allocator_free(alloc);
    return 0;
}
