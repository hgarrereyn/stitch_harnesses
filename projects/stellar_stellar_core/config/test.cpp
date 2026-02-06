#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stellar-core/util/Algorithm.h>

int main() {
    std::vector<std::string> data = {"apple", "apricot", "banana", "blueberry", "avocado"};
    auto groups = split<std::string>(data, [](std::string const& s){ return s[0]; });
    // Print counts per initial letter
    for (auto const& kv : groups) {
        std::cout << kv.first << ":" << kv.second.size() << "\n";
    }
    return 0;
}
