#include <iostream>
#include <string>
#include <vector>
#include <simdutf.h>

int main() {
    const char *src = "Hello, \xF0\x9F\x98\x80"; // Hello, 😀
    size_t len = std::char_traits<char>::length(src);
    bool ok = simdutf::validate_utf8(src, len);
    if(!ok) { std::cout << "invalid utf8" << std::endl; return 0; }

    size_t utf16_needed = simdutf::utf16_length_from_utf8(src, len);
    std::u16string utf16(utf16_needed, 0);
    size_t written16 = simdutf::convert_utf8_to_utf16le(src, len, reinterpret_cast<char16_t*>(utf16.data()));

    size_t utf8_needed = simdutf::utf8_length_from_utf16(utf16.data(), written16);
    std::string roundtrip(utf8_needed, 0);
    size_t written8 = simdutf::convert_utf16le_to_utf8(utf16.data(), written16, roundtrip.data());

    // Exercise base64 as well
    std::string payload = "Test";
    size_t b64len = simdutf::base64_length_from_binary(payload.size());
    std::string b64(b64len, '\0');
    simdutf::binary_to_base64(payload.data(), payload.size(), b64.data());
    std::vector<char> back(simdutf::maximal_binary_length_from_base64(b64.data(), b64.size()));
    simdutf::result r = simdutf::base64_to_binary(b64.data(), b64.size(), back.data());

    std::cout << ok << " " << written16 << " " << written8 << " " << r.count << "\n";
    return 0;
}
