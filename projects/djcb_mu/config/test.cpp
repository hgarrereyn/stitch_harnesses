#include <iostream>
#include "utils/mu-utils.hh"

int main() {
    std::string who = "world";
    // exercise a tiny bit of the public API (fmt + glib logging wrappers)
    std::string msg = Mu::mu_format("Hello, {}!", who);
    Mu::mu_info("Test message: {}", msg);
    std::cout << msg << std::endl;
    return 0;
}
