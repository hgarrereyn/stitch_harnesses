#include <iostream>
#include <vector>
#include <string>
#include <OpenHashTab/openhashtab.h>

int main() {
    const std::string msg = "OpenHashTab fuzz setup test";
    const std::string enc = b64::encode(reinterpret_cast<const uint8_t*>(msg.data()), msg.size());
    const std::vector<uint8_t> dec = b64::decode(enc.c_str(), enc.size());
    std::string roundtrip(dec.begin(), dec.end());

    std::cout << "Encoded: " << enc << "\n";
    std::cout << "Decoded: " << roundtrip << "\n";

    if (roundtrip != msg) return 1;
    return 0;
}
