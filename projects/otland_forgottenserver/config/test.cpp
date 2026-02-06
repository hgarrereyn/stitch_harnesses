#include "otpch.h"
#include "base64.h"
#include <iostream>

int main() {
    std::string data = "hello world";
    auto enc = tfs::base64::encode(data);
    auto dec = tfs::base64::decode(enc);
    std::cout << enc << "\n" << dec << "\n";
    return 0;
}
