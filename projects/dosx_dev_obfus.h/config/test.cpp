#include <iostream>

#define NO_OBF 1
#include "obfus.h"

int main() {
    // With NO_OBF, macros devolve to standard operations and no Windows/TCC-specific code is pulled in
    int sum = VM_ADD(2, 3);
    const char* msg = HIDE_STRING("Hello from obfus.h (disabled)");
    std::cout << "sum=" << sum << ", msg=" << msg << std::endl;
    return 0;
}
