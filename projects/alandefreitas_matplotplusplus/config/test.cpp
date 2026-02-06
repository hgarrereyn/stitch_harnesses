#include <matplot/matplot.h>
#include <vector>
#include <iostream>
int main() {
    // Use some utility APIs without invoking any backend
    std::vector<double> x = matplot::linspace(0.0, 1.0, 11);
    auto y = matplot::transform(x, [](double v){ return v*v; });
    std::cout << "ok " << x.size() << " " << y.back() << "\n";
    return 0;
}
