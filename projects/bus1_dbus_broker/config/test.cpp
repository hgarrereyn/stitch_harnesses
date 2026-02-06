#include <iostream>
#include "util/common.h"

int main() {
    // Use a tiny bit of the project API (an enum from util/common.h)
    int a = UTIL_TRISTATE_UNSET;
    int b = UTIL_TRISTATE_YES;
    int c = UTIL_TRISTATE_NO;
    std::cout << "Tristate: " << a << "," << b << "," << c << std::endl;
    return 0;
}
