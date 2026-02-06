#include <iostream>
#include <cstring>
extern "C" {
#include <lldpctl.h>
}

int main() {
    const char* transport = lldpctl_get_default_transport();
    if (!transport) {
        std::cout << "no transport" << std::endl;
        return 0;
    }
    lldpctl_log_level(1);
    lldpctl_conn_t* conn = lldpctl_new_name(transport, nullptr, nullptr, nullptr);
    if (!conn) {
        // Allocation failure would be surprising; still ok for a smoke test
        std::cout << "failed to create connection handle" << std::endl;
        return 0;
    }
    // Do not actually talk to daemon; just create and destroy handle
    int rc = lldpctl_release(conn);
    std::cout << "release rc=" << rc << " transport=" << transport << std::endl;
    return 0;
}
