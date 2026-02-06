#include <QtNodes/Definitions>
#include <QtNodes/ConnectionIdUtils>
#include <iostream>

int main() {
    using namespace QtNodes;
    // Create a simple connection id and manipulate it
    ConnectionId conn{1u, 0u, 2u, 1u};

    // Print connection id
    std::cout << "ConnectionId: ";
    std::cout << conn; // operator<< is defined in ConnectionIdUtils

    // Convert to/from JSON to exercise Qt dependency linkage
    QJsonObject obj = toJson(conn);
    ConnectionId conn2 = fromJson(obj);

    if (conn != conn2) {
        std::cerr << "Roundtrip JSON failed" << std::endl;
        return 1;
    }

    // Use small helper functions
    auto outId = getNodeId(PortType::Out, conn2);
    auto inId  = getNodeId(PortType::In, conn2);

    if (outId != 1u || inId != 2u) return 2;

    return 0;
}
