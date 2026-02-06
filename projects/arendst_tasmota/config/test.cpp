#include <cstdio>
#include <cstdint>
#include <cstring>
#include <FastCRC.h>

int main() {
    const char* msg = "hello world";
    FastCRC32 crc32;
    uint32_t v = crc32.crc32(reinterpret_cast<const uint8_t*>(msg), strlen(msg));
    std::printf("CRC32(\"%s\") = 0x%08x\n", msg, v);
    FastCRC16 crc16;
    uint16_t m = crc16.modbus(reinterpret_cast<const uint8_t*>(msg), strlen(msg));
    std::printf("MODBUS16(\"%s\") = 0x%04x\n", msg, m);
    return 0;
}
