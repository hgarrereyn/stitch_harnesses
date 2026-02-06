#include <iostream>
#include <srsran/version.h>

int main() {
    // Only use macros/constants from the public API to avoid needing to link
    std::cout << "srsRAN version (macro): " << SRSRAN_VERSION_STRING << "\n";
    // Also check encoded version macro
    std::cout << "Encoded version: " << SRSRAN_VERSION << "\n";
    return 0;
}
