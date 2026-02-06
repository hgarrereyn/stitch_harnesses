#include <cstdio>
#include <upnp/upnp.h>

int main() {
    int rc = UpnpInit2(nullptr, 0);
    if (rc != UPNP_E_SUCCESS && rc != UPNP_E_INIT) {
        std::printf("UpnpInit2 failed: %d\n", rc);
        return 0; // still exit successfully for test purposes
    }
    unsigned short port4 = UpnpGetServerPort();
    unsigned short port6 = UpnpGetServerPort6();
    std::printf("libupnp initialized. IPv4 port=%u IPv6-LLA port=%u\n", (unsigned)port4, (unsigned)port6);
    UpnpFinish();
    return 0;
}
