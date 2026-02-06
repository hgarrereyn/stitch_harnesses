#include <pcap/pcap.h>
#include <cstdio>
int main() {
    const char* v = pcap_lib_version();
    if (v) {
        std::printf("libpcap: %s\n", v);
    } else {
        std::printf("libpcap version unknown\n");
    }
    return 0;
}
