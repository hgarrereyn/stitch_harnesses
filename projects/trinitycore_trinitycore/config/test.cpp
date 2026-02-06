#include <iostream>
#include "Common.h"

int main() {
    LocaleConstant loc = GetLocaleByName("enUS");
    if (!IsValidLocale(loc)) {
        std::cout << "Invalid locale" << std::endl;
        return 1;
    }
    std::cout << "Locale index: " << (int)loc << ", name: " << localeNames[loc] << std::endl;
    auto bit = WowLocaleToCascLocaleBit[loc];
    std::cout << "CASC bit: " << (int)bit << std::endl;
    return 0;
}
