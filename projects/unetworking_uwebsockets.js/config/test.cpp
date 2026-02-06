#include <iostream>
#include "FastTimers.h"

static int fired = 0;

void mycb() {
    fired++;
}

int main() {
    init();
    // Set a timer for 20ms => two ticks of component 0 (10ms each)
    unsigned int t = setTimeout_(mycb, 20);

    // Simulate time passing by ticking component 0 twice
    tick(0);
    tick(0);

    // Clean up timer data structures
    clearTimeout_(t);

    std::cout << "Timers fired: " << fired << std::endl;
    return fired == 1 ? 0 : 1;
}
