#include "pcap_wrapper.h"
#include <cstdio>

int main() {
    // Use an inline function from the project to verify headers work
    pcap_t *p = nullptr; // dummy handle
    int rc = pcap_set_immediate_mode(p, 1);
    std::printf("pcap_set_immediate_mode returned %d\n", rc);
    return 0;
}
