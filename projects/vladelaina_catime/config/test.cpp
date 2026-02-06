#include <iostream>
extern "C" {
#include "utils/string_safe.h"
}

int main() {
    char buf[32];
    int n1 = safe_strncpy(buf, "Hello", sizeof(buf));
    int n2 = safe_strncat(buf, ", Catime!", sizeof(buf));
    std::cout << "buf='" << buf << "' n1=" << n1 << " n2=" << n2 << "\n";
    return 0;
}
