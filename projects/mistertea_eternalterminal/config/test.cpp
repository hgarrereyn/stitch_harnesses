#include <iostream>
#include <string>
#include <base/Packet.hpp>
#include <base/TcpSocketHandler.hpp>

int main() {
    using namespace et;
    // Construct a simple packet and serialize/deserialize it
    Packet p1(42, std::string("hello"));
    std::string wire = p1.serialize();
    Packet p2(wire);

    if (p2.getHeader() != 42 || p2.getPayload() != "hello" || p2.isEncrypted()) {
        std::cerr << "Packet roundtrip failed" << std::endl;
        return 1;
    }

    // Instantiate a TCP socket handler (no network activity performed)
    TcpSocketHandler handler;

    std::cout << "OK: header=" << int(p2.getHeader())
              << " payload='" << p2.getPayload() << "'\n";
    return 0;
}
