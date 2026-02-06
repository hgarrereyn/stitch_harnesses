#include <cstdio>
#include <pcap.h>
extern "C" {
#include "netdissect.h"
#include "print.h"
}

int main() {
    char errbuf[256];
    if (nd_init(errbuf, sizeof(errbuf)) != 0) {
        std::printf("nd_init failed: %s\n", errbuf);
        return 1;
    }

    netdissect_options ndo{}; // zero-initialize
    ndo.program_name = "tcpdump_test";
    ndo.ndo_vflag = 1; // be a bit verbose
    ndo_set_function_pointers(&ndo);

    // Initialize address/printing context
    init_print(&ndo, 0, 0xFFFFFFFF);

    // Choose a simple link-layer printer (DLT_NULL is widely supported)
    if_printer printer = get_if_printer(DLT_NULL);
    if (!printer) {
        std::printf("No printer for DLT_NULL\n");
        nd_cleanup();
        return 0; // still success; at least we linked
    }
    ndo.ndo_if_printer = printer;

    // Construct a tiny dummy packet: 4-byte AF header + minimal payload
    unsigned char pkt[8] = {0};
    struct pcap_pkthdr h{};
    h.ts.tv_sec = 0; h.ts.tv_usec = 0;
    h.caplen = sizeof(pkt);
    h.len = sizeof(pkt);

    // Exercise pretty_print_packet (should not crash)
    pretty_print_packet(&ndo, &h, pkt, 1);

    nd_cleanup();
    return 0;
}
