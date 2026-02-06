#include <cstdio>
#include <pcap/pcap.h>

int main() {
    const char* ver = pcap_lib_version();
    std::printf("libpcap version: %s\n", ver ? ver : "unknown");

    char errbuf[PCAP_ERRBUF_SIZE] = {0};
    pcap_t* pd = pcap_open_dead(DLT_RAW, 65535);
    if (!pd) {
        std::puts("pcap_open_dead failed");
        return 1;
    }

    struct bpf_program fp;
    const char* filter = "tcp or udp";
    if (pcap_compile(pd, &fp, filter, 1 /* optimize */, PCAP_NETMASK_UNKNOWN) == 0) {
        std::puts("Filter compiled OK");
        pcap_freecode(&fp);
    } else {
        std::printf("pcap_compile failed: %s\n", pcap_geterr(pd));
    }

    pcap_close(pd);
    return 0;
}
