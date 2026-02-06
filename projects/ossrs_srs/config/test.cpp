#include <srs_core.hpp>
#include <iostream>

int main() {
    SrsContextId cid;
    cid.set_value("hello-srs");
    std::cout << "Server: " << RTMP_SIG_SRS_SERVER << " | Ctx: " << cid.c_str() << std::endl;
    return 0;
}
