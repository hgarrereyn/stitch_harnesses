#include <iostream>
#include "Multiprotocol.h"

int main() {
    // Use a couple of enums and defines from the public header
    int major = VERSION_MAJOR;
    int minor = VERSION_MINOR;
    PROTOCOLS p = PROTO_FRSKYX;
    std::cout << "Multiprotocol version " << major << "." << minor << ", example protocol id: " << (int)p << "\n";
    return 0;
}
