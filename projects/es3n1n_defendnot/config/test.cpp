#include <iostream>
#include <string>
#include "defendnot_api.hpp"

int main() {
    std::string who = "world";
    std::cout << defendnot_api::greet(who) << " (" << defendnot_api::version() << ")" << std::endl;
    return 0;
}
