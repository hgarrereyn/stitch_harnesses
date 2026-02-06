#include <iostream>
#include <qbittorrent/expected.hpp>

int main() {
    nonstd::expected<int, std::string> val = 42;
    if (val) {
        std::cout << "Expected holds: " << *val << "\n";
    } else {
        std::cout << "Unexpected: " << val.error() << "\n";
    }
    return 0;
}
