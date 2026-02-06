#include <stdio.h>
#include <libwebsockets.h>

int main() {
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));
    info.port = CONTEXT_PORT_NO_LISTEN;

    struct lws_context *ctx = lws_create_context(&info);
    if (!ctx) {
        printf("Failed to create lws context\n");
        return 1;
    }

    const char *ver = lws_get_library_version();
    if (ver)
        printf("libwebsockets version: %s\n", ver);

    lws_service(ctx, 0);

    lws_context_destroy(ctx);
    printf("lws context created and destroyed successfully\n");
    return 0;
}
