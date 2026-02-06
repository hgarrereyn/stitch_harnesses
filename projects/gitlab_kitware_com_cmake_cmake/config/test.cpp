#include <iostream>
#include <cmVersion.h>

int main() {
    std::cout << "CMake version: " << cmVersion::GetCMakeVersion() << "\n";
    std::cout << "Major: " << cmVersion::GetMajorVersion() << ".";
    std::cout << cmVersion::GetMinorVersion() << ".";
    std::cout << cmVersion::GetPatchVersion() << " (tweak " << cmVersion::GetTweakVersion() << ")\n";
    return 0;
}
