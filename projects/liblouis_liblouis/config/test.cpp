#include <iostream>
#include <liblouis.h>

int main() {
    const char* ver = lou_version();
    int cs = lou_charSize();
    if (!ver || cs <= 0) {
        std::cout << "Liblouis not working" << std::endl;
        return 1;
    }
    std::cout << "liblouis version: " << ver << ", char size: " << cs << std::endl;
    // Also call a couple more API functions to ensure linkage
    lou_setLogLevel(LOU_LOG_OFF);
    lou_free();
    return 0;
}
