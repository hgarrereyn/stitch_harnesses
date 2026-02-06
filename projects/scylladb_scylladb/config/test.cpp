#include <iostream>
#include <vector>
#include <string>
#include "cartesian_product.hh"

int main() {
    std::vector<std::vector<std::string>> v = {
        {"a", "b"},
        {"1", "2", "3"}
    };
    size_t expected = cartesian_product_size(v);
    size_t count = 0;
    cartesian_product<std::string> cp(v);
    auto it = cp.begin();
    auto end = cp.end();
    while (!(it == end)) {
        auto &combo = *it;
        std::string s;
        for (auto &e : combo) s += e;
        ++count;
        ++it;
    }
    std::cout << "count=" << count << ", expected=" << expected << "\n";
    return count == expected ? 0 : 1;
}
