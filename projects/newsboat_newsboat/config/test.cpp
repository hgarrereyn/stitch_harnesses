#include <iostream>
#include <string>
#include "strprintf.h"

int main() {
    std::string who = "World";
    std::string msg = newsboat::strprintf::fmt("Hello, %s! The answer is %d.", who, 42);
    std::cout << msg << std::endl;
    return 0;
}
