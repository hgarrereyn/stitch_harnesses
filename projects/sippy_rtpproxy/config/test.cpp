#include <iostream>
#include <librtpproxy.h>

int main() {
    const char *args[] = {"rtpproxy", "-h"};
    // Initialize using the library entrypoint; with -h this should not start daemon
    struct rtpp_cfg *cfg = rtpp_main(2, args);
    if (cfg != nullptr) {
        // Cleanly shutdown if anything was initialized
        rtpp_shutdown(cfg);
    }
    std::cout << "librtpproxy loaded and symbols resolved" << std::endl;
    return 0;
}
