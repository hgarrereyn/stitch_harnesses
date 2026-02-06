#include <re2/re2.h>
#include <iostream>
#include <string>

int main() {
    std::string s;
    int i = 0;
    // Simple match and capture using RE2 API
    if (RE2::FullMatch("ruby:1234", "(\\w+):(\\d+)", &s, &i)) {
        std::cout << s << ":" << i << "\n";
    } else {
        std::cout << "no match\n";
    }

    // Precompiled RE2 object
    RE2 re("h.*o");
    if (!re.ok()) return 1;
    bool m1 = RE2::FullMatch("hello", re);
    bool m2 = RE2::PartialMatch("hello", re);
    std::cout << (m1 ? "full" : "no_full") << "," << (m2 ? "partial" : "no_partial") << "\n";
    return 0;
}
