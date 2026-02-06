extern "C" {
#include <nxt_unit.h>
}
#include <cstring>
#include <cstdio>

int main() {
    const char* header = "Content-Type";
    uint16_t h = nxt_unit_field_hash(header, std::strlen(header));
    std::printf("hash=%u\n", (unsigned)h);
    return 0;
}
