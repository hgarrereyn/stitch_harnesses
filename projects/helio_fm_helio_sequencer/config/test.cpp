#include <iostream>
#include "helio_minimal.h"

int main() {
    std::cout << "ticksPerBeat=" << Globals::ticksPerBeat << "\n";
    constexpr auto h = constexprHash("test");
    std::cout << "hash=" << h << "\n";
    return 0;
}
