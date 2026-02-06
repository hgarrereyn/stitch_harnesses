#include <snappy.h>
#include <string>
#include <iostream>

int main() {
    const std::string input = "hello hello hello hello world world world!";
    std::string compressed;
    std::string uncompressed;

    snappy::Compress(input.data(), input.size(), &compressed);

    bool ok = snappy::Uncompress(compressed.data(), compressed.size(), &uncompressed);

    std::cout << "Input: " << input.size() 
              << ", Compressed: " << compressed.size() 
              << ", Uncompressed: " << uncompressed.size() 
              << ", OK: " << (ok && uncompressed == input ? "true" : "false") 
              << std::endl;
    return ok && uncompressed == input ? 0 : 1;
}
