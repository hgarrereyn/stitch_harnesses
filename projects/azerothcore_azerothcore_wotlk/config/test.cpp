#include <iostream>
#include "SharedDefines.h"

int main() {
    // Use a couple of public definitions to ensure headers are usable
    SpellEffIndex idx = EFFECT_1;
    float tol = GROUND_HEIGHT_TOLERANCE;
    std::cout << "Idx:" << static_cast<int>(idx) << ", Tol:" << tol << std::endl;
    return 0;
}
