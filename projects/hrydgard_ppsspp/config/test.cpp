#include <iostream>
#include "Common/Swap.h"

int main() {
    unsigned int x = 0x11223344u;
    unsigned int y = bswap32(x);
    std::cout << std::hex << y << std::endl;
    return 0;
}
