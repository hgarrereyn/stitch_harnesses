#include <iostream>
#include <snort/utils/bits.h>
#include <snort/main/snort_types.h>

int main() {
    PortBitSet ports;
    ports.set(80);
    ports.set(443);
    std::cout << "Set ports: " << ports.count() << "\n";
    uint64_t v = 123456789ULL;
    char buf[64];
    snprintf(buf, sizeof(buf), STDu64, v);
    std::cout << "Value: " << buf << "\n";
    return 0;
}
