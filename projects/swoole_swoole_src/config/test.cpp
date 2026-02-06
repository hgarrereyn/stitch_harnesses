#include <cstdio>
#include <cstring>
#include <string>
#include "/fuzz/install/include/swoole/swoole_api.h"

int main() {
    const char* ver = swoole_version();
    int ver_id = swoole_version_id();
    int api_id = swoole_api_version_id();
    if (!ver) {
        printf("Failed to get Swoole version\\n");
        return 1;
    }
    printf("Swoole version: %s (ver_id=%d, api_id=%d)\\n", ver, ver_id, api_id);
    return 0;
}
