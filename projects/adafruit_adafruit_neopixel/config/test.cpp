#include <iostream>
#include <cstdint>
#include <Adafruit_NeoPixel.h>

int main() {
    uint32_t packed = Adafruit_NeoPixel::Color(10, 20, 30);
    uint8_t s = Adafruit_NeoPixel::sine8(64);
    uint8_t g = Adafruit_NeoPixel::gamma8(128);

    std::cout << "Packed: 0x" << std::hex << packed << std::dec
              << ", sine8(64): " << (int)s
              << ", gamma8(128): " << (int)g << std::endl;
    return 0;
}
