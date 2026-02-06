#include <pybind11/pybind11.h>
#include <iostream>

int main() {
    std::cout << "pybind11 major.minor: "
              << PYBIND11_VERSION_MAJOR << "."
              << PYBIND11_VERSION_MINOR << std::endl;
    return 0;
}
