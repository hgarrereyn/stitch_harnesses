#include <iostream>
#include <string>
#include "/fuzz/install/include/wiliwili/utils/number_helper.hpp"

int main() {
    std::string s = wiliwili::pre0(7, 3); // expect 007
    std::cout << "pre0(7,3)=" << s << "\n";
    return 0;
}
