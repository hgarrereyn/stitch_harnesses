#include <iostream>
#include <string>
#include <re2/re2.h>

int main() {
    std::string text = "The answer is 42.";
    int num = 0;
    bool matched = RE2::PartialMatch(text, "(\\d+)", &num);
    std::cout << "Matched: " << (matched ? "yes" : "no") << ", num=" << num << "\n";
    // Also test options object to ensure headers and linking are fine
    RE2::Options opt; opt.set_log_errors(false);
    RE2 re("^The answer is (\\d+)\\.$", opt);
    std::string whole;
    if (re.ok()) {
        RE2::FullMatch(text, re, &num);
    }
    return 0;
}
