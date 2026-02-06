#include <iostream>
extern "C" {
#include <libavutil/avutil.h>
}
int main() {
    unsigned v = avutil_version();
    const char* ver = av_version_info();
    const char* cfg = avutil_configuration();
    const char* lic = avutil_license();
    std::cout << "libavutil version int: " << v << "\n";
    std::cout << "libavutil version: " << (ver ? ver : "?") << "\n";
    std::cout << "configuration: " << (cfg ? cfg : "?") << "\n";
    std::cout << "license: " << (lic ? lic : "?") << "\n";
    return 0;
}
