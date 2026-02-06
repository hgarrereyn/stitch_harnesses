#include <iostream>
#include <polyhook2/Misc.hpp>

int main() {
    // Simple smoke test for a couple of header-only utilities
    uint64_t addr = 0x1234;
    uint64_t aligned_up = PLH::AlignUpwards(addr, 0x1000);
    uint64_t aligned_down = PLH::AlignDownwards(addr, 0x1000);

    std::string hex = PLH::int_to_hex<uint32_t>(0xDEADBEEF);

    std::cout << "aligned_up=" << aligned_up
              << ", aligned_down=" << aligned_down
              << ", hex=" << hex << std::endl;
    return 0;
}
