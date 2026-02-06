#include <iostream>
#include "ExtruderPrime.h"

int main() {
    cura::ExtruderPrime mode = cura::ExtruderPrime::Prime;
    if (mode == cura::ExtruderPrime::Prime) {
        std::cout << "CuraEngine header OK: ExtruderPrime::Prime" << std::endl;
    }
    return 0;
}
