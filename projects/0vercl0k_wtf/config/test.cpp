#include <iostream>
#include "kdmp-parser.h"

int main() {
    std::cout << "kdmp-parser version: " << KDMPPARSER_VERSION_RELEASE << "\n";
    std::cout << "Page size constant: " << kdmpparser::Page::Size << "\n";
    return 0;
}
