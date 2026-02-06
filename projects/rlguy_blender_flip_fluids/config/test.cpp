#include <iostream>
#include <flipfluids/engine/fluidsimulation.h>

int main() {
    try {
        FluidSimulation sim(4, 4, 4, 0.1); // small grid
        int maj=0, min=0, rev=0;
        sim.getVersion(&maj, &min, &rev);
        std::cout << "FFEngine Version: " << maj << "." << min << "." << rev << "\n";
        std::cout << "Initialized? " << (sim.isInitialized() ? "yes" : "no") << "\n";
        sim.setCurrentFrame(1);
        std::cout << "Current frame: " << sim.getCurrentFrame() << "\n";
    } catch (const std::exception &e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
    return 0;
}
