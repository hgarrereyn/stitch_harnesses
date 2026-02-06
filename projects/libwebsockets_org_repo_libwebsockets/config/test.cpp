#include <cstdio>
#include <libwebsockets.h>

int main() {
    lws_context_creation_info info;
    memset(&info, 0, sizeof(info));
    info.port = CONTEXT_PORT_NO_LISTEN; // no listening socket

    lws_context* context = lws_create_context(&info);
    if (!context) {
        std::printf("Failed to create lws context\n");
        return 1;
    }

    lws_service(context, 0);

    lws_context_destroy(context);
    std::printf("libwebsockets context created and destroyed successfully\n");
    return 0;
}
