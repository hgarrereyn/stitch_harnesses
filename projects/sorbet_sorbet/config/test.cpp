#include <iostream>
#include "sorbet_version/sorbet_version.h"

int main() {
    std::cout << "Sorbet version: " << sorbet_getFullVersionString() << "\n";
    std::cout << "Release build? " << sorbet_getIsReleaseBuild() << ", with debug symbols? "
              << sorbet_getIsWithDebugSymbols() << "\n";
    return 0;
}
