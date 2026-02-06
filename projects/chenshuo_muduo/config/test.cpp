#include <muduo/net/Buffer.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Timestamp.h>
#include <iostream>

int main() {
    // Use Buffer API
    muduo::net::Buffer buf;
    std::string msg = "hello muduo";
    buf.append(msg);
    std::string out = buf.retrieveAllAsString();

    // Use InetAddress API
    muduo::net::InetAddress addr(12345);
    std::string ipport = addr.toIpPort();

    // Use Timestamp API
    muduo::Timestamp now = muduo::Timestamp::now();

    std::cout << "Buffer roundtrip: " << out << "\n";
    std::cout << "InetAddress: " << ipport << "\n";
    std::cout << "Timestamp: " << now.toString() << "\n";
    return 0;
}
