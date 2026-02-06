#include <mpv/client.h>
#include <cstdio>

int main(){
    mpv_handle *ctx = mpv_create();
    if (!ctx) { std::printf("mpv_create failed\n"); return 0; }
    unsigned long v = mpv_client_api_version();
    std::printf("libmpv api version: %lu\n", v);
    mpv_terminate_destroy(ctx);
    return 0;
}
