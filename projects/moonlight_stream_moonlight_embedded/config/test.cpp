#include <cstdio>
#include <cstring>
extern "C" {
#include "client.h"
#include "discover.h"
#include "xml.h"
#include <Limelight.h>
}

int main() {
    const char* xml = "<root><Mode width=\"1920\" height=\"1080\" refresh=\"60\"/></root>";
    PDISPLAY_MODE modes = nullptr;
    int r = xml_modelist((char*)xml, (size_t)std::strlen(xml), &modes);
    std::printf("xml_modelist ret=%d\n", r);
    SERVER_DATA server{};
    server.httpPort = 47984;
    (void)server;
    return 0;
}
