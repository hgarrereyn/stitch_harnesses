#include <iostream>
#include <gsl/gsl>
#include <gsl/span>
#include <gsl/narrow>

int main() {
    int data[5] = {1, 2, 3, 4, 5};
    gsl::span<int> s(data);
    int sum = 0;
    for (int v : s) sum += v;

    // Use gsl::narrow to convert safely
    try {
        auto small = gsl::narrow<short>(sum);
        std::cout << "sum=" << sum << ", small=" << small << "\n";
    } catch (const gsl::narrowing_error&) {
        std::cout << "narrowing_error caught\n";
    }

    // Use not_null
    int value = 42;
    gsl::not_null<int*> ptr(&value);
    *ptr = *ptr + 1;
    std::cout << "value=" << value << "\n";
    return 0;
}
