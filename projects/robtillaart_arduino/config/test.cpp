#include <iostream>
#include <vector>
#include <CRC.h>

int main() {
    const char* msg = "Hello CRC";
    const uint8_t* data = reinterpret_cast<const uint8_t*>(msg);
    crc_size_t len = (crc_size_t)std::char_traits<char>::length(msg);

    uint32_t c32 = calcCRC32(data, len);

    CRC8 c8; c8.add(data, len);
    uint8_t v8 = c8.calc();

    CRC16 c16; c16.add(data, len);
    uint16_t v16 = c16.calc();

    std::cout << "CRC32: " << c32 << " CRC16: " << v16 << " CRC8: " << (unsigned)v8 << std::endl;
    return 0;
}
