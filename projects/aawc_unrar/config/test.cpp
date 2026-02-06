#include <iostream>
#include "dll.hpp"

int main() {
    int ver = RARGetDllVersion();
    std::cout << "UNRAR DLL version: " << ver << "\n";
    // Basic sanity: version should be positive
    if (ver <= 0) return 1;
    return 0;
}
