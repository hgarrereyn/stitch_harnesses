#include <iostream>
#include <osgEarth/Version>

int main() {
    const char* ver = osgEarthGetVersion();
    const char* sover = osgEarthGetSOVersion();
    std::cout << "osgEarth version: " << (ver ? ver : "unknown")
              << ", soversion: " << (sover ? sover : "unknown") << std::endl;
    osgEarth::Version parsed = osgEarth::parseVersion(ver ? ver : "0.0.0");
    std::cout << "Parsed: " << parsed.major << "." << parsed.minor << "." << parsed.patch << std::endl;
    return 0;
}
