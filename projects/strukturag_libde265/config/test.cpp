#include <libde265/de265.h>
#include <cstdio>

int main() {
    const char* v = de265_get_version();
    std::printf("libde265 version: %s\n", v ? v : "unknown");

    de265_decoder_context* ctx = de265_new_decoder();
    if (!ctx) {
        std::printf("failed to create decoder context\n");
        return 1;
    }

    int more = 0;
    de265_error err = de265_decode(ctx, &more);
    const char* errtxt = de265_get_error_text(err);
    std::printf("decode status: %s (more=%d)\n", errtxt ? errtxt : "", more);

    de265_free_decoder(ctx);
    return 0;
}
