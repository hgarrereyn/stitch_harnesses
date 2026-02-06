#include <cstdio>
#include <cstdint>
#include <cstring>
#include <jbig2.h>

static void err_cb(void *data, const char *msg, Jbig2Severity severity, uint32_t seg_idx) {
    (void)data; (void)seg_idx;
    const char *sev = (severity==JBIG2_SEVERITY_FATAL?"FATAL":
                       severity==JBIG2_SEVERITY_WARNING?"WARN":
                       severity==JBIG2_SEVERITY_INFO?"INFO":"DEBUG");
    std::printf("[jbig2dec %s] %s\n", sev, msg);
}

int main() {
    Jbig2Ctx *ctx = jbig2_ctx_new(nullptr, (Jbig2Options)0, nullptr, err_cb, nullptr);
    if (!ctx) { std::printf("failed to create context\n"); return 0; }

    // Feed an empty buffer and complete a page (simulating EOP on broken stream)
    const unsigned char dummy[1] = {0};
    jbig2_data_in(ctx, dummy, 0);
    jbig2_complete_page(ctx);

    Jbig2Image *img = jbig2_page_out(ctx);
    if (img) {
        std::printf("Got image: %ux%u, stride=%u\n", img->width, img->height, img->stride);
        jbig2_release_page(ctx, img);
    } else {
        std::printf("No image produced (as expected for empty input)\n");
    }

    jbig2_ctx_free(ctx);
    return 0;
}
