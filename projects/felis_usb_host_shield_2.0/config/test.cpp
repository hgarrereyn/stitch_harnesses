#include <iostream>
#include "AMBXEnums.h"

int main() {
    AmbxColorsEnum c = AmbxColorsEnum::Blue;
    AmbxLightsEnum light = AmbxLightsEnum::Sidelight_left;
    unsigned int color = static_cast<unsigned int>(c);
    unsigned int l = static_cast<unsigned int>(light);
    std::cout << "Color: 0x" << std::hex << color << ", Light: 0x" << l << std::endl;
    return 0;
}
