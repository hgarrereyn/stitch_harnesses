#include <iostream>
#include <Wt/WString.h>

int main() {
    Wt::WString s = Wt::WString::fromUTF8("Hello, Wt!");
    std::cout << s.toUTF8() << std::endl;
    return 0;
}
