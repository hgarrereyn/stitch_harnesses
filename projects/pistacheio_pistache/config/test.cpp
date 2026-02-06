#include <iostream>
#include <string>
#include <vector>
#include <pistache/base64.h>
#include <pistache/mime.h>
#include <pistache/version.h>

int main() {
    // Simple Base64 encode/decode roundtrip using Pistache API
    std::string input = "pistache-test";
    std::vector<std::byte> raw;
    raw.reserve(input.size());
    for (unsigned char c : input) raw.push_back(std::byte(c));

    Base64Encoder enc(raw);
    const std::string &b64 = enc.Encode();

    Base64Decoder dec(b64);
    const auto &decoded = dec.Decode();

    std::string roundtrip;
    roundtrip.reserve(decoded.size());
    for (auto b : decoded) roundtrip.push_back(static_cast<char>(b));

    // Use a small bit of the MIME API too
    auto plain = MIME(Text, Plain);

    std::cout << "b64=" << b64 << " roundtrip=" << roundtrip
              << " mime=" << plain.toString()
              << " ver=" << Pistache::Version::Major << "." << Pistache::Version::Minor << "." << Pistache::Version::Patch
              << std::endl;

    return roundtrip == input ? 0 : 1;
}
