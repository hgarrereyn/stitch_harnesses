#include <iostream>
#include "xorshift_prng.h"

int main() {
    XorShift128PlusPlus rng(12345u);
    auto val = rng.Next();
    std::cout << "Random: " << (unsigned long long)val << "\n";
    return 0;
}
