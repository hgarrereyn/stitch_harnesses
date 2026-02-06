#include <iostream>
#include <tl/expected.hpp>

// Simple functions to exercise tl::expected API
static tl::expected<int, std::string> parse_int(const std::string &s) {
    try {
        int v = std::stoi(s);
        return v;
    } catch (...) {
        return tl::make_unexpected(std::string{"bad number"});
    }
}

int main() {
    // success path
    auto e1 = parse_int("42");
    if (e1) {
        auto doubled = e1.map([](int v) { return v * 2; });
        std::cout << "ok:" << *doubled << "\n";
    }

    // error path + map_error/or_else
    auto e2 = parse_int("not-a-number");
    auto msg = e2.map_error([](const std::string &err) { return std::string{"err:"} + err; })
                  .or_else([](const std::string &msg){ std::cout << msg << "\n"; return tl::expected<int, std::string>{0}; });
    (void)msg;

    // and_then chain
    auto e3 = parse_int("5").and_then([](int v) -> tl::expected<int, std::string> { return v + 7; });
    if (e3) std::cout << "sum:" << *e3 << "\n";

    return 0;
}
