#include <iostream>
#include <string>
#include "doris/util/md5.h"

int main() {
    const std::string input = "hello world";

    doris::Md5Digest md5;
    md5.update(input.data(), input.size());
    md5.digest();

    std::cout << "MD5: " << md5.hex() << "\n";
    return 0;
}
