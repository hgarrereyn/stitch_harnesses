#include <iostream>
#include "libsumo/libsumo.h"

int main() {
    auto v = libsumo::Simulation::getVersion();
    std::cout << "TraCI version: " << v.first << " name: " << v.second << std::endl;
    return 0;
}
