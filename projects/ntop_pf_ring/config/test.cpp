#include <iostream>
#include <pfring.h>

int main() {
    // Just exercise a small portion of the API without requiring PF_RING kernel/module
    // Use some struct definitions and constants, and format output.
    pfring_packet_info info{};
    info.caplen = 0;
    info.len = 0;
    info.flags = 0;
    info.hash = 0;

    // Print known version from installed header linux/pf_ring.h via macro RING_VERSION
#ifdef RING_VERSION
    std::cout << "PF_RING header version: " << RING_VERSION << "\n";
#else
    std::cout << "PF_RING header version macro not found\n";
#endif

    // Basic enums/structs usage to ensure linkage works
    filtering_mode mode = software_only;
    (void)mode;

    std::cout << "Test OK\n";
    return 0;
}
