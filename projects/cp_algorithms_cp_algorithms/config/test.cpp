#include <iostream>
#include <vector>
#include <string>
#include "cp_algorithms.h"

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    long long s = cpalgorithms::sum(v);
    std::string b = cpalgorithms::banner();
    std::cout << b << " sum=" << s << "\n";
    return 0;
}
