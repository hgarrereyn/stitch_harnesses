#include <iostream>
extern "C" {
#include "/fuzz/install/include/common.h"
}

int main() {
    // Resolve localhost:80 and print a nicely formatted string using sslh helpers
    struct addrinfo *ai = nullptr;
    char buf[256];
    resolve_split_name(&ai, (char*)"localhost", (char*)"80");
    if (ai) {
        sprintaddr(buf, sizeof(buf), ai);
        std::cout << "Resolved: " << buf << std::endl;
    } else {
        std::cout << "No addrinfo returned" << std::endl;
    }
    return 0;
}
