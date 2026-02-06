#include <iostream>
#include <cstdint>
#include <Keyboard_def.h>

int main() {
#ifdef MARAUDER_CARDPUTER
    // Use the ASCII map to lookup a few characters
    uint8_t a = _kb_asciimap['a'];
    uint8_t A = _kb_asciimap['A'];
    uint8_t one = _kb_asciimap['1'];
    std::cout << "a=" << (int)a << ", A=" << (int)A << ", 1=" << (int)one << std::endl;
#else
    std::cout << "MARAUDER_CARDPUTER not defined" << std::endl;
#endif
    return 0;
}
