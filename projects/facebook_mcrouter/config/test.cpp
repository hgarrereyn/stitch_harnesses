#include <iostream>
#include <cstring>
#include <mcrouter/lib/fbi/hash.h>

int main() {
    const char* key = "example_key";
    size_t len = std::strlen(key);
    uint32_t m = 128; // number of buckets
    uint32_t idx = furc_hash(key, len, m);
    uint32_t crc = crc32_hash(key, len);
    std::cout << "furc_hash(" << key << ") mod " << m << " = " << idx << "\n";
    std::cout << "crc32_hash(" << key << ") = " << crc << "\n";
    return (idx < m) ? 0 : 1;
}
