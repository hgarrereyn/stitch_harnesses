#include <iostream>
#include <ninja/version.h>

int main() {
    int major = 0, minor = 0;
    ParseVersion(std::string(kNinjaVersion), &major, &minor);
    std::cout << "Ninja version: " << kNinjaVersion << " (" << major << "." << minor << ")\n";
    // Basic sanity: parse a custom version string
    int M = 0, m = 0; 
    ParseVersion("1.2.3", &M, &m);
    std::cout << "Parsed 1.2.3 -> " << M << "." << m << "\n";
    return 0;
}
