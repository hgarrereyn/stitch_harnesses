#include <iostream>
#include <string>
#include <vector>
#include <utf8cpp/utf8.h>

int main() {
    // Simple UTF-8 string containing multi-byte characters
    std::string s = "Hello, \xE6\x97\xA5\xD1\x88!"; // "Hello, 日ш!"

    // Validate
    bool ok = utf8::is_valid(s);
    if (!ok) {
        std::cout << "Invalid UTF-8 input" << std::endl;
        return 0;
    }

    // Convert to UTF-16 and back
    std::u16string u16 = utf8::utf8to16(s);
    std::string round = utf8::utf16to8(u16);

    // Compute distance
    auto dist = utf8::distance(s.begin(), s.end());

    std::cout << "Valid: " << ok << ", codepoints: " << dist 
              << ", roundtrip equal: " << (round == s) << std::endl;
    return 0;
}
