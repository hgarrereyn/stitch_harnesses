#include <iostream>
#include <ctime>
#include "pdns/gettime.hh"

int main() {
    struct timespec ts{};
    int rc = gettime(&ts, false);
    std::cout << "gettime rc=" << rc << ", sec=" << ts.tv_sec << ", nsec=" << ts.tv_nsec << std::endl;
    return 0;
}
