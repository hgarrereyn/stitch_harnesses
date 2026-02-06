#include <iostream>
#include "w2l_shim.h"

int main() {
    const char* v = w2l_shim_version();
    std::cout << "Shim version: " << v << std::endl;
    return 0;
}
