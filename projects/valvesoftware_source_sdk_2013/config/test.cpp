#include <tier1/snappy.h>
#include <string>
#include <iostream>

int main() {
    const std::string input = "hello hello hello hello hello";
    std::string compressed;
    std::string uncompressed;
    snappy::Compress(input.data(), input.size(), &compressed);
    if (!snappy::Uncompress(compressed.data(), compressed.size(), &uncompressed)) {
        std::cout << "uncompress failed" << std::endl;
        return 1;
    }
    std::cout << uncompressed << std::endl;
    return uncompressed == input ? 0 : 2;
}
