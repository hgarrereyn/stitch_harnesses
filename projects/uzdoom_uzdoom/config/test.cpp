#include <cstdio>
#include <cstdlib>
#include <zmusic.h>

int main() {
    const ZMusicConfigurationSetting* cfg = ZMusic_GetConfiguration();
    if (cfg && cfg->name) {
        std::printf("First ZMusic config: %s (id=%d)\n", cfg->name, cfg->identifier);
    } else {
        std::printf("ZMusic configuration not available or empty.\n");
    }

    const char* err = ZMusic_GetLastError();
    std::printf("Last ZMusic error: %s\n", err ? err : "<none>");
    return 0;
}
