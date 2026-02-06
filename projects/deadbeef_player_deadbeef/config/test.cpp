#include <iostream>
#include <deadbeef/deadbeef.h>

int main() {
    std::cout << "DeaDBeeF API version: " << DB_API_VERSION_MAJOR << "." << DB_API_VERSION_MINOR << std::endl;
    DB_plugin_t plugin = {0};
    plugin.api_vmajor = DB_API_VERSION_MAJOR;
    plugin.api_vminor = DB_API_VERSION_MINOR;
    plugin.type = DB_PLUGIN_MISC;
    plugin.version_major = 1;
    plugin.version_minor = 0;
    plugin.id = (char*)"fuzz_test_plugin";
    plugin.name = (char*)"Fuzz Test Plugin";
    std::cout << "Plugin struct prepared: " << plugin.name << std::endl;
    return 0;
}
