#include <base/likely.h>
#include <iostream>

int main() {
    int x = 0;
    for (int i = 0; i < 1000; ++i) {
        if (likely(i < 999)) {
            x += 1;
        } else if (unlikely(i == 999)) {
            x += 2;
        }
    }
    std::cout << "x=" << x << "\n";
    return 0;
}
