#include <iostream>
#include "Common/json/json.hpp"
#include "Common/CppCodec/base64_default_rfc4648.hpp"

int main() {
    // Use header-only APIs vendored in the project
    nlohmann::json j;
    j["hello"] = "world";
    std::string s = j.dump();

    // Base64 encode/decode using CppCodec
    std::string encoded = cppcodec::base64_rfc4648::encode(s);
    std::string decoded = cppcodec::base64_rfc4648::decode<std::string>(encoded);

    // Verify roundtrip
    if (decoded != s) return 1;

    // Print something trivial to ensure runtime
    std::cout << decoded << std::endl;
    return 0;
}
