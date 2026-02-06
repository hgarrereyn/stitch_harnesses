#include <stdio.h>
#include <netdb.h>
extern "C" {
#include "/fuzz/install/include/core.h"
#include "/fuzz/install/include/rdns.h"
}

int main() {
    core_initialize();
    rdns_init(DNSLF_LIBC);

    struct addrinfo *res = NULL;
    int rc = proxy_getaddrinfo("localhost", "80", NULL, &res);
    if (rc == 0 && res) {
        proxy_freeaddrinfo(res);
    }

    proxychains_write_log(const_cast<char*>("proxychains test completed, rc=%d\n"), rc);
    core_unload();
    return 0;
}
