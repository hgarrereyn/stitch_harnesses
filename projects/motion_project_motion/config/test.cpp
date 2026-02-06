#include <iostream>
#include "motion.hpp"
#include "util.hpp"

int main() {
    // Exercise a tiny piece of the public API (macro)
    SLEEP(0, 1000000); // 1 ms

    MOTION_SIGNAL sig = MOTION_SIGNAL_NONE;
    DEVICE_STATUS st = STATUS_INIT;
    ctx_all_loc loc{};

    std::cout << "Motion headers OK: sig=" << sig << ", st=" << st << ", row=" << loc.row << "\n";
    return 0;
}
