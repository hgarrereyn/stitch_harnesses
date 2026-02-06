#include <tins/tins.h>
#include <iostream>

int main() {
    using namespace Tins;
    try {
        IP ip("192.0.2.1", "198.51.100.2");
        TCP tcp(80, 12345);
        tcp.set_flag(TCP::SYN, 1);
        auto pkt = ip / tcp;
        std::cout << "Packet size: " << pkt.size() << " bytes\n";
    } catch (std::exception& ex) {
        std::cout << "Exception: " << ex.what() << "\n";
    }
    return 0;
}
