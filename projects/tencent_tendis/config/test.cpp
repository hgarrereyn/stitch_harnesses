#include <iostream>
#include <string>
#include "/fuzz/install/include/optional.h"

int main() {
    // Use the header-only optional implementation bundled with Tendis
    std::experimental::optional<int> oi; // initially disengaged
    oi = 42;                              // assign a value
    if (oi) {
        std::cout << "optional has value: " << *oi << "\n";
    } else {
        std::cout << "optional empty\n";
    }
    // Reset and verify empty state
    oi = std::experimental::nullopt;
    std::cout << (oi ? "not empty" : "now empty") << "\n";
    return 0;
}
