#include <iostream>
#include <cstring>
#include <vector>
#include <djitools.h>

int main() {
    std::cout << "DJI Tools shim version: " << djitools::version() << "\n";
    const char* msg = "DJI";
    int sum = djitools::simple_checksum(reinterpret_cast<const unsigned char*>(msg), (int)std::strlen(msg));
    std::cout << "Checksum('DJI')=" << sum << "\n";
    // Basic sanity assertion-like check to ensure library is usable
    if (sum <= 0) return 1;
    return 0;
}
