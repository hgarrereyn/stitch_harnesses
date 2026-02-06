#include <immer/vector.hpp>
#include <iostream>

int main() {
    // Create a persistent vector and perform some operations
    immer::vector<int> v;
    auto v1 = v.push_back(1);
    auto v2 = v1.push_back(2).push_back(3).set(1, 5);
    // Access elements and compute a small sum
    long long sum = 0;
    for (auto x : v2) sum += x;
    std::cout << "sum=" << sum << " size=" << v2.size() << " first=" << v2[0] << "\n";
    return 0;
}
