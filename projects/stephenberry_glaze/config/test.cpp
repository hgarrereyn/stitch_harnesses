#include <iostream>
#include <glaze/version.hpp>

int main() {
    std::cout << (int)glz::version.major << "."
              << (int)glz::version.minor << "."
              << (int)glz::version.patch << "\n";
    return 0;
}
