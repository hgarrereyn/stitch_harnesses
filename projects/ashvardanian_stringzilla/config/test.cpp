#include <iostream>
#include <string>
#include <cstring>
#include <stringzilla/stringzilla.hpp>

int main() {
    namespace sz = ashvardanian::stringzilla;

    sz::string haystack = "Hello, StringZilla!";
    sz::string_view needle = "String";

    auto pos = haystack.find(needle);
    if (pos == sz::string::npos) return 1;

    // Hash a view and verify basic properties
    auto hv = std::hash<sz::string_view>{}(haystack);
    (void)hv;

    // Basic UTF-8 case folding API smoke test (C API)
    const char* src = "Stra\xC3\x9F" "e"; // "Straße"
    char dst[64];
    sz_size_t folded_len = sz_utf8_case_fold(src, (sz_size_t)std::strlen(src), dst);
    if (folded_len == 0 || dst[0] != 's') return 2;

    std::cout << "OK: pos=" << pos << ", folded_len=" << folded_len << std::endl;
    return 0;
}
