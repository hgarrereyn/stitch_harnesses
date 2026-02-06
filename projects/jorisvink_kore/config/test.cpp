#include <kore/kore.h>
#include <iostream>

int main() {
    std::cout << "Kore test running" << std::endl;
    std::cout << "KORE_RSAKEY_BITS=" << KORE_RSAKEY_BITS << std::endl;
    std::cout << "KORE_TLS_VERSION_1_3=" << KORE_TLS_VERSION_1_3 << std::endl;

    netbuf nb{}; // zero-initialize
    nb.type = NETBUF_SEND;
    nb.flags = 0;
    nb.buf = nullptr;

    std::cout << "netbuf size=" << sizeof(nb) << std::endl;
    return 0;
}
