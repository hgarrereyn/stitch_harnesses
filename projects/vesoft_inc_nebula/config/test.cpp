#include <iostream>
#include <string>
#include "common/base/MurmurHash2.h"

int main() {
    nebula::MurmurHash2 hasher;
    std::string s = "nebula-graph";
    size_t h = hasher(s);
    std::cout << "hash(" << s << ")=" << h << std::endl;
    // basic checks to use more API variants
    const char* cs = "nebula-graph";
    size_t h2 = hasher(cs);
    if (h != h2) {
        std::cerr << "mismatch" << std::endl;
        return 1;
    }
    return 0;
}
