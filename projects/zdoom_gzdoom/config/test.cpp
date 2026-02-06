#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "zmusic.h"

int main() {
    const ZMusicConfigurationSetting* cfg = ZMusic_GetConfiguration();
    int count = 0;
    if (cfg) {
        while (cfg[count].name && cfg[count].name[0] != '\0') {
            count++;
            if (count > 5) break;
        }
    }
    const char* err = ZMusic_GetLastError();
    if (err) {
        volatile size_t len = std::strlen(err);
        (void)len;
    }
    printf("ZMusic config entries observed: %d\n", count);
    return 0;
}
