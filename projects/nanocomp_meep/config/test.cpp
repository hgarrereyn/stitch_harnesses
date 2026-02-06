#include <iostream>
#include <vector>
#include "meep.hpp"

int main() {
    std::vector<double> x = meep::linspace(0.0, 1.0, 5);
    std::cout << "linspace size: " << x.size() << "\n";
    double sum = 0.0;
    for (double v : x) sum += v;
    std::cout << "sum: " << sum << "\n";
    return 0;
}
