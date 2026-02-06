#include <iostream>
#include <vector>
#include <cppitertools/itertools.hpp>

int main() {
    using namespace iter;
    std::vector<int> v{1,2,3,4,5};
    long sum = 0;
    for (auto i : range(1, 6)) {
        sum += i;
    }
    // also touch enumerate and accumulate to ensure headers are fine
    long sum2 = 0;
    for (auto&& [idx, val] : enumerate(v)) {
        (void)idx; // silence unused warning
        sum2 += val;
    }
    long acc_last = 0;
    for (auto x : accumulate(v)) {
        acc_last = x; // final value is total sum
    }
    std::cout << "sum=" << sum << ", sum2=" << sum2 << ", acc_last=" << acc_last << "\n";
    return 0;
}
