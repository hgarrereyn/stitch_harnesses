#include <iostream>
#include <musikcore/musikcore_c.h>

int main() {
    std::cout << "musikcore C API version: " << mcsdk_version << std::endl;
    return 0;
}
