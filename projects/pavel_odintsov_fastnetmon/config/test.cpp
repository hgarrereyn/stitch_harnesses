#include <iostream>
#include "iana_ip_protocols.hpp"

int main() {
    const char* name_tcp = get_ip_protocol_name_by_number_iana(6);
    const char* name_udp = get_ip_protocol_name_by_number_iana(17);
    std::cout << (name_tcp ? name_tcp : "null") << "," << (name_udp ? name_udp : "null") << "\n";
    return 0;
}
