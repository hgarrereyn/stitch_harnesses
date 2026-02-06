#include <ctre.hpp>
#include <string>
#include <string_view>
#include <iostream>

static constexpr auto pattern = ctll::fixed_string{"h.*"};

int main() {
    std::string_view sv = "hello world";
    if (auto m = ctre::match<pattern>(sv)) {
        // Convert to string to exercise API
        std::string s = m.to_string();
        std::cout << s.substr(0, 5) << "\n"; // print "hello"
    }
    return 0;
}
