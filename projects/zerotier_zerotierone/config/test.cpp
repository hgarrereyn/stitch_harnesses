#include <iostream>
#include <ZeroTierOne.h>

int main() {
    std::cout << "ZeroTier constants: "
              << "DEFAULT_PORT=" << ZT_DEFAULT_PORT
              << ", MIN_MTU=" << ZT_MIN_MTU
              << ", MAX_MTU=" << ZT_MAX_MTU
              << std::endl;
    return 0;
}
