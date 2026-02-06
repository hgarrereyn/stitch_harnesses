#include <qrtplib/rtpsession.h>
#include <iostream>

int main() {
    qrtplib::RTPSession session; // Do not initialize sockets, just default construct
    std::cout << "RTPSession object created" << std::endl;
    return 0;
}
