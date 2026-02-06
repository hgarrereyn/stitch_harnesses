#include <iostream>
#include <cstring>
extern "C" {
#include "misc.h"
}
int main() {
    char buf[32];
    std::memset(buf, 0, sizeof(buf));
    strnzcpy(buf, "Hello, JtR inline!", sizeof(buf));
    std::cout << buf << std::endl;
    return 0;
}
