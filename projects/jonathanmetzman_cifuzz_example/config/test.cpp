#include <iostream>
#include <string>
#include "my_api.h"

int main() {
    std::string s1 = "hello";
    std::string s2 = "foobar";
    size_t r1 = DoStuff(s1);
    size_t r2 = DoStuff(s2);
    std::cout << "Results: " << r1 << ", " << r2 << "\n";
    return 0;
}
