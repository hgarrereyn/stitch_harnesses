#include <cstdio>
#include <cstdint>
extern "C" {
#include <crc16.h>
}

int main() {
    const char* msg = "hello world";
    uint16_t c = crc16(msg, 11);
    std::printf("crc16(\"%s\") = %u\n", msg, (unsigned)c);
    return 0;
}
