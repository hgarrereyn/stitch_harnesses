#include <iostream>
#include "utils.h"

using namespace similarity;

int main() {
    // Use a couple of API utilities
    int r = RandomInt();
    double vals[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double mean = Mean(vals, 5);
    const char* base = GetFileName("/tmp/some/path/file.txt");

    std::cout << "rand=" << r << ", mean=" << mean << ", base=" << base << std::endl;
    // Exercise a function implemented in the library (not header-only)
    bool host_exists = DoesFileExist("/etc/hostname");
    std::cout << "hostname exists=" << (host_exists ? "yes" : "no") << std::endl;
    return 0;
}
