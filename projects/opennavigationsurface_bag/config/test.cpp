#include <iostream>
#include <cstdlib>
#include "bag.h"

int main() {
    // Point BAG home to the installed configdata so calls that need it can find XMLs
    bagSetHomeFolder("/fuzz/install/configdata");

    // Just print version info from generated header to verify linkage/headers
    std::cout << "BAG version: " << BAG_VERSION << " (" << BAG_VER_MAJOR << "." << BAG_VER_MINOR << "." << BAG_VER_REVISION << ")\n";

    // Exercise a trivial API surface: allocate and free a small buffer
    uint8_t* buf = bagAllocate(16);
    if (!buf) {
        std::cerr << "bagAllocate returned null" << std::endl;
        return 1;
    }
    for (int i = 0; i < 16; ++i) buf[i] = static_cast<uint8_t>(i);
    bagFree(buf);

    std::cout << "BAG basic API call succeeded" << std::endl;
    return 0;
}
