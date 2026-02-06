#include <iostream>
#include "cppcheck/cppcheck.h"

int main() {
    std::cout << "Cppcheck version: " << CppCheck::version() << "\n";
    return 0;
}
