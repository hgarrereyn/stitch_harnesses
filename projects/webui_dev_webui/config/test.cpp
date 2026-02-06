#include <cstdio>
#include <cstring>
#include "webui.h"

int main() {
    // Simple sanity checks on non-UI utilities that don't require spawning a browser
    const char* text = "Hello WebUI";
    char* b64 = webui_encode(text);
    if (!b64) {
        std::printf("encode failed\n");
        return 1;
    }
    char* dec = webui_decode(b64);
    if (!dec) {
        webui_free(b64);
        std::printf("decode failed\n");
        return 1;
    }
    bool ok = std::strcmp(dec, text) == 0;

    // Exercise a few lightweight APIs
    size_t w = webui_new_window();
    size_t free_port = webui_get_free_port();
    (void)free_port;
    webui_set_timeout(0);
    webui_destroy(w);

    webui_free(b64);
    webui_free(dec);

    std::printf("ok=%d\n", ok ? 1 : 0);
    return ok ? 0 : 1;
}
