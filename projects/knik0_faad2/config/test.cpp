#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <neaacdec.h>

int main() {
    // Print version
    char *id = nullptr; char *copy = nullptr;
    if (NeAACDecGetVersion(&id, &copy) == 0) {
        std::printf("FAAD2 version: %s\n", id ? id : "unknown");
        if (copy) std::printf("%s\n", copy);
    }

    // Open decoder
    NeAACDecHandle h = NeAACDecOpen();
    if (!h) {
        std::fprintf(stderr, "Failed to open decoder\n");
        return 1;
    }

    // Get and set configuration
    NeAACDecConfigurationPtr conf = NeAACDecGetCurrentConfiguration(h);
    if (conf) {
        conf->outputFormat = FAAD_FMT_16BIT;
        conf->downMatrix = 0;
        NeAACDecSetConfiguration(h, conf);
    }

    // We won't actually decode any data here; just ensure basic API works
    NeAACDecClose(h);
    std::puts("FAAD2 basic API test completed.");
    return 0;
}
