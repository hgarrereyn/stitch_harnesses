#include <cstdio>
#include <cstring>
#include <string>

extern "C" {
#include "dropbear/pubkeyapi.h"
}

int main() {
    // Verify we can reference the public API symbols/types
    int major = DROPBEAR_PLUGIN_VERSION_MAJOR;
    int minor = DROPBEAR_PLUGIN_VERSION_MINOR;

    // Create a dummy PluginInstance and set function pointers to nullptr
    PluginInstance inst{};
    inst.api_version[0] = major;
    inst.api_version[1] = minor;
    inst.checkpubkey = nullptr;
    inst.auth_success = nullptr;
    inst.delete_session = nullptr;
    inst.delete_plugin = nullptr;

    // And a dummy PluginSession
    PluginSession sess{};
    sess.plugin_instance = &inst;
    sess.get_options = nullptr;

    // Print something to ensure the program runs
    std::printf("Dropbear EPKA version: %d.%d\n", major, minor);
    return 0;
}
