#include <iostream>
#include <string>
#include <system_error>
#include "fast_float/fast_float.h"

int main() {
    using namespace fast_float;

    // Parse a double
    std::string s = "3.14159 xyz";
    double d = 0.0;
    auto r1 = from_chars(s.data(), s.data() + s.size(), d);
    if (r1.ec != std::errc()) {
        std::cerr << "double parse failed\n";
        return 1;
    }

    // Parse an integer (decimal)
    std::string i_str = "12345";
    int i = 0;
    auto r2 = from_chars(i_str.data(), i_str.data() + i_str.size(), i);
    if (r2.ec != std::errc()) {
        std::cerr << "int parse failed\n";
        return 1;
    }

    // Use advanced options: JSON should reject leading plus
    std::string bad = "+1.0";
    double dj = 0.0;
    parse_options opts{chars_format::json};
    auto r3 = from_chars_advanced(bad.data(), bad.data() + bad.size(), dj, opts);

    std::cout << "parsed double: " << d << " int: " << i
              << " json err set: " << (r3.ec != std::errc()) << "\n";
    return 0;
}
