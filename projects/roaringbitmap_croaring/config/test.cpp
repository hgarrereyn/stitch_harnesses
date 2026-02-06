#include <iostream>
#include <roaring/roaring.hh>
#include <roaring/roaring64map.hh>
#include <roaring/roaring.h>

int main() {
    // Test 32-bit Roaring bitmap (C++ API)
    roaring::Roaring r32;
    for (uint32_t i = 100; i < 110; ++i) r32.add(i);
    if (!r32.contains(105)) return 1;
    std::cout << "r32 card=" << r32.cardinality() << "\n";

    // Test 64-bit Roaring bitmap (C++ API)
    roaring::Roaring64Map r64;
    for (uint64_t i = 1000; i < 1010; ++i) r64.add(i);
    if (!r64.contains(static_cast<uint64_t>(1005))) return 2;
    std::cout << "r64 card=" << r64.cardinality() << "\n";

    // Quick C API sanity via portable serialization size
    roaring_bitmap_t* c32 = roaring_bitmap_create();
    roaring_bitmap_add(c32, 1);
    roaring_bitmap_add(c32, 2);
    size_t sz = roaring_bitmap_portable_size_in_bytes(c32);
    std::cout << "c32 sz=" << sz << "\n";
    roaring_bitmap_free(c32);

    return 0;
}
