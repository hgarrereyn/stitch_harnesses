#include <iostream>
#include <NumCpp.hpp>

int main() {
    // Create a simple array and perform a few NumCpp operations
    nc::NdArray<double> a = nc::linspace<double>(1.0, 5.0, 5);
    auto b = nc::square(a);
    double s = nc::sum(b).item();

    std::cout << "a: " << a << "\n";
    std::cout << "b (square): " << b << "\n";
    std::cout << "sum(b): " << s << "\n";

    // A small linalg op
    nc::NdArray<double> m = {{1.0, 2.0}, {3.0, 4.0}};
    auto mt = nc::transpose(m);
    auto dotp = nc::dot(m, mt);
    std::cout << "m: \n" << m << "\n";
    std::cout << "m * m^T: \n" << dotp << "\n";
    return 0;
}
