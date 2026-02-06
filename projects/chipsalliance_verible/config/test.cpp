#include <iostream>
#include <map>
#include <string>
#include <string_view>

#include "verible/common/strings/compare.h"

int main() {
    // Use the header-only StringViewCompare comparator from Verible
    std::map<std::string, int, verible::StringViewCompare> m;
    m["apple"] = 1;
    m["banana"] = 2;
    m["cherry"] = 3;

    std::string_view key = "banana";
    auto it = m.find(key); // heterogeneous lookup works via StringViewCompare
    if (it != m.end()) {
        std::cout << it->first << ":" << it->second << "\n";
        return 0;
    }
    std::cout << "not found\n";
    return 0;
}
