#include <iostream>
#include <string>
#include "/fuzz/install/include/myanmartools.h"

int main() {
    google_myanmar_tools::ZawgyiDetector detector;
    const char* uni = "မြန်မာစာ"; // Myanmar text in Unicode
    const char* zg  = "ျမန္မာစာ"; // Likely to be interpreted as Zawgyi-encoded bytes

    double p_uni = detector.GetZawgyiProbability(uni);
    double p_zg  = detector.GetZawgyiProbability(zg);

    std::cout << "P(zg|uni sample)=" << p_uni << "\n";
    std::cout << "P(zg|zg sample)=" << p_zg << "\n";

    // Ensure program runs deterministically
    std::cout << "OK" << std::endl;
    return 0;
}
