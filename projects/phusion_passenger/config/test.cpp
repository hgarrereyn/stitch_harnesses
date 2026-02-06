#include <iostream>
#include "StaticString.h"

int main() {
    Passenger::StaticString s("hello passenger");
    std::cout << "StaticString size=" << s.size() << ", data='" << std::string(s.data(), s.size()) << "'\n";
    return 0;
}
