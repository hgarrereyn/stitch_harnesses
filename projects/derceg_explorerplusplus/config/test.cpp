#include <iostream>
#include <Explorer++/ValueWrapper.h>

int main() {
    ValueWrapper<int> v(0);
    int observed = -1;
    auto conn = v.addObserver([&](int newVal){ observed = newVal; });

    v.set(42);
    std::cout << "Value is " << v.get() << ", observed " << observed << "\n";
    if (observed != 42) return 1;
    conn.disconnect();
    return 0;
}
