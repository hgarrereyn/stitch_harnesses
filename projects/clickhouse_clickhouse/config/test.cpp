#include <iostream>
#include <pcg_random.hpp>

int main() {
    pcg32 rng(42u); // seed with constant for reproducibility
    uint32_t x = rng();
    std::cout << "pcg32 number: " << x << "\n";
    return 0;
}
