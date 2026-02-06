#include <rfb/rfb.h>
#include <cstdlib>
#include <cstdio>

int main() {
    int argc = 1;
    char* argv[] = { (char*)"test", nullptr };
    rfbScreenInfoPtr server = rfbGetScreen(&argc, argv, 32, 32, 8, 3, 4);
    if (!server) {
        std::fprintf(stderr, "rfbGetScreen failed\n");
        return 1;
    }
    server->frameBuffer = (char*)std::calloc(32 * 32, 4);
    if (!server->frameBuffer) return 1;
    rfbInitServer(server);
    rfbMarkRectAsModified(server, 0, 0, 1, 1);
    return 0;
}
