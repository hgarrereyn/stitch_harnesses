#include <iostream>
#include <string>
#include <ILuaModuleManager.h>

int main() {
    CChecksum chk{};
    chk.ulCRC = 0xDEADBEEF;
    for (int i = 0; i < 16; ++i) chk.mD5[i] = static_cast<unsigned char>(i);

    std::cout << "Checksum CRC: 0x" << std::hex << chk.ulCRC << std::dec << "\n";
    std::cout << "MD5 first byte: " << static_cast<int>(chk.mD5[0]) << "\n";

    lua_State* L = nullptr; // reference Lua type to verify headers are usable
    (void)L;

    std::cout << "Test program ran successfully." << std::endl;
    return 0;
}
