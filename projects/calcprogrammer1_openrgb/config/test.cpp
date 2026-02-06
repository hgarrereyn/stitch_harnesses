#include <iostream>
#include <string>
#include "NetworkProtocol.h"
#include "StringUtils.h"

int main() {
    // Test NetworkProtocol API
    NetPacketHeader hdr{};
    InitNetPacketHeader(&hdr, 2u, NET_PACKET_ID_REQUEST_PROTOCOL_VERSION, sizeof(NetPacketHeader));

    // Validate magic bytes and print a small summary
    bool magic_ok = (hdr.pkt_magic[0]=='O' && hdr.pkt_magic[1]=='R' && hdr.pkt_magic[2]=='G' && hdr.pkt_magic[3]=='B');

    // Test StringUtils utilities
    std::u16string u16 = u"Hello\0\0"; // include a couple trailing nulls
    std::string s = StringUtils::u16string_to_string(u16);
    std::string cleaned = StringUtils::remove_null_terminating_chars(s + std::string("\0\0", 2));

    std::cout << "MagicOK=" << magic_ok
              << ", DevIdx=" << hdr.pkt_dev_idx
              << ", PktId=" << hdr.pkt_id
              << ", Size=" << hdr.pkt_size
              << ", Cleaned='" << cleaned << "'\n";
    return 0;
}
