#include <iostream>
#include "string_utils.h"

int main() {
    // Use a few header-only utilities to avoid heavy deps
    std::string s = "  hello,world , typesense  ";
    std::vector<std::string> parts;
    StringUtils::split(s, parts, ",", /*keep_empty*/false, /*trim_space*/true);
    std::cout << "parts=" << parts.size() << "\n";

    std::string joined = StringUtils::join(parts, "|");
    std::cout << "joined=" << joined << "\n";

    std::string b64 = StringUtils::base64_encode("typesense");
    std::cout << "b64=" << b64 << "\n";

    bool is_int = StringUtils::is_integer("12345");
    bool is_float = StringUtils::is_float("12.34");
    std::cout << "is_int=" << is_int << ", is_float=" << is_float << "\n";

    // Ensure Option works
    Option<int> ok(42);
    std::cout << "option_ok=" << ok.ok() << ", val=" << ok.get() << "\n";

    return 0;
}
