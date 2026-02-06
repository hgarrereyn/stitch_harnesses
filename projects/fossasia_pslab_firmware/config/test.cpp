#include <iostream>
#include <cstdint>
extern "C" {
#include "commands.h"
#include "states.h"
}

int main() {
    // Use constants/types from the firmware headers to ensure they compile and are usable
    uint32_t total_groups = NUM_PRIMARY_CMDS;
    state_t s = STATE_STANDBY;
    std::cout << "PSLab firmware header test: groups=" << total_groups
              << ", state=" << static_cast<int>(s) << std::endl;
    // Do not call any firmware functions (they are MCU-specific). Just link against the dummy lib.
    return 0;
}
