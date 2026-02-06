#include <iostream>
#include "PcapPlusPlusVersion.h"
#include "EthLayer.h"
#include "IPv4Layer.h"
#include "UdpLayer.h"
#include "PayloadLayer.h"
#include "Packet.h"

int main() {
    // Print version info
    std::cout << "PcapPlusPlus version: " << pcpp::getPcapPlusPlusVersionFull() << "\n";

    // Build a simple Ethernet/IPv4/UDP packet with payload
    pcpp::EthLayer eth(pcpp::MacAddress("01:02:03:04:05:06"), pcpp::MacAddress("06:05:04:03:02:01"));
    pcpp::IPv4Layer ip(pcpp::IPv4Address("192.0.2.1"), pcpp::IPv4Address("192.0.2.2"));
    ip.getIPv4Header()->timeToLive = 64;
    pcpp::UdpLayer udp(12345, 80);
    uint8_t payloadData[] = { 'h','e','l','l','o' };
    pcpp::PayloadLayer payload(payloadData, sizeof(payloadData));

    pcpp::Packet packet(100);
    packet.addLayer(&eth);
    packet.addLayer(&ip);
    packet.addLayer(&udp);
    packet.addLayer(&payload);
    packet.computeCalculateFields();

    std::cout << "Total packet length: " << packet.getRawPacket()->getRawDataLen() << " bytes\n";
    // Verify some basic properties
    if (!packet.isPacketOfType(pcpp::IPv4) || !packet.isPacketOfType(pcpp::UDP)) {
        std::cerr << "Packet type detection failed" << std::endl;
        return 1;
    }

    auto ipv4 = packet.getLayerOfType<pcpp::IPv4Layer>();
    auto udpL = packet.getLayerOfType<pcpp::UdpLayer>();
    if (!ipv4 || !udpL) {
        std::cerr << "Layer extraction failed" << std::endl;
        return 1;
    }

    std::cout << "Src IP: " << ipv4->getSrcIPv4Address() << ", Dst IP: " << ipv4->getDstIPv4Address() << "\n";
    std::cout << "Src Port: " << udpL->getUdpHeader()->portSrc << ", Dst Port: " << udpL->getUdpHeader()->portDst << "\n";

    return 0;
}
