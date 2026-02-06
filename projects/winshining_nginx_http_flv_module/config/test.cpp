#include <iostream>
#include "ngx_rtmp_version.h"

int main() {
    std::cout << "NGINX RTMP module version: " << NGINX_RTMP_VERSION << "\\n";
    // Use the numeric version macro too
    std::cout << "Numeric version: " << nginx_rtmp_version << "\\n";
    return 0;
}
