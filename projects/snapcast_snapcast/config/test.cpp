#include <iostream>
#include "common/base64.h"
#include "common/sample_format.hpp"

int main() {
    std::string text = "hello fuzz";
    std::string enc = base64_encode(text);
    std::string dec = base64_decode(enc);

    SampleFormat fmt(48000, 16, 2);
    std::cout << "Encoded: " << enc << "\n";
    std::cout << "Decoded: " << dec << "\n";
    std::cout << "Format: " << fmt.toString() << "\n";
    return 0;
}
