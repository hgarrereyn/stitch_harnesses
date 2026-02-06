#include <SafeInt/SafeInt.hpp>
#include <iostream>

int main() {
    // Basic use of SafeInt: perform checked addition
    SafeInt<int> a = 1000000;
    SafeInt<int> b = 2000000;
    auto c = a + b; // still within int range
    std::cout << "Result: " << static_cast<int>(c) << "\n";
    return 0;
}
