#include <iostream>
#include <goldleaf_compat.hpp>

int main() {
    std::cout << "Version: " << goldleaf_compat::version() << "\n";
    std::cout << "2 + 3 = " << goldleaf_compat::add(2, 3) << "\n";
    return 0;
}
