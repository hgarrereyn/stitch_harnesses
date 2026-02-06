#include <cstdio>
#include <cstring>
#include <sys/stat.h>
extern "C" {
#include <anet.h>
}

int main() {
    char err[ANET_ERR_LEN];
    char ip[64];
    std::memset(err, 0, sizeof(err));
    std::memset(ip, 0, sizeof(ip));
    int rc = anetResolve(err, (char*)"localhost", ip);
    if (rc == ANET_OK) {
        std::printf("Resolved localhost to %s\n", ip);
    } else {
        std::printf("anetResolve failed: %s\n", err);
    }
    return 0;
}
