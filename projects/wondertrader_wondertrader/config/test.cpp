#include <iostream>
#include "WTSUtils/WTSCfgLoader.h"
#include "Includes/WTSVariant.hpp"

int main() {
    const char* json = "{\"name\":\"wt\",\"value\":123}";
    WTSVariant* v = WTSCfgLoader::load_from_content(std::string(json), false);
    if (v) {
        std::cout << "Loaded config variant successfully." << std::endl;
    } else {
        std::cout << "Failed to load variant." << std::endl;
    }
    return 0;
}
