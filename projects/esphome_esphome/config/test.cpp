#include <iostream>
#include "esphome/components/xxtea/xxtea.h"

int main() {
    // Example data: 4 words (16 bytes)
    uint32_t data[4] = {0x11223344u, 0x55667788u, 0x99aabbccu, 0xddeeff00u};
    const uint32_t key[8] = {0u,1u,2u,3u,4u,5u,6u,7u};

    esphome::xxtea::encrypt(data, 4, key);
    esphome::xxtea::decrypt(data, 4, key);

    // After decrypt, data should be original
    uint64_t checksum = 0;
    for (auto w : data) checksum = (checksum * 1315423911ULL) ^ w;
    std::cout << "Checksum: " << checksum << "\n";
    return 0;
}
