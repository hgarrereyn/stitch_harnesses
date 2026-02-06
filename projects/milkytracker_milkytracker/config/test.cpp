#include <iostream>
#include <cstdint>
#include <milkyplay/MilkyPlayTypes.h>
#include <milkyplay/LittleEndian.h>

int main() {
    // Prepare a small little-endian buffer and use the utility to read values
    unsigned char data[6] = { 0x34, 0x12, 0x78, 0x56, 0x9a, 0xbc };
    mp_uword w = LittleEndian::GET_WORD(data);        // 0x1234
    mp_uint32 d = LittleEndian::GET_DWORD(data + 2);  // 0x56789abc
    std::cout << "WORD=" << w << ", DWORD=" << d << "\n";
    return 0;
}
