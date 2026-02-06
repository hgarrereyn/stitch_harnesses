#include <iostream>
#include "common/String.h"
#include "common/Format.h"

int main() {
    String hello = String::Build("Hello, ", String::value_type('W'), String::value_type('o'), String::value_type('r'), String::value_type('l'), String::value_type('d'));
    ByteString utf8 = hello.ToUtf8();
    String formatted = String::Build(hello, String::value_type('!'), ' ', Format::Hex(255), ' ', Format::Dec(42));

    std::cout << utf8.c_str() << std::endl;
    std::cout << formatted.ToUtf8().c_str() << std::endl;
    return 0;
}
