#include <iostream>
#include "commons/Util.h"

int main() {
    std::string s = "alpha,beta,gamma";
    auto parts = Util::split(s, ",");
    std::cout << "Parts: " << parts.size() << "\n";
    for (size_t i = 0; i < parts.size(); ++i) {
        std::cout << i << ": " << parts[i] << "\n";
    }
    // Simple call to a tiny function to ensure linkage
    char buf[64];
    Util::fastSeqIdToBuffer(0.5f, buf);
    std::cout << "SeqId buffer: " << buf << "\n";
    return 0;
}
