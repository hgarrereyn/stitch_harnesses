#include <cstdio>
#include <spng.h>

int main() {
    const char* ver = spng_version_string();
    std::printf("libspng version: %s\n", ver ? ver : "(null)");

    spng_ctx* ctx = spng_ctx_new(0);
    if (!ctx) {
        std::printf("Failed to create spng context\n");
        return 1;
    }

    // Set some reasonable image limits (no-op for this test)
    spng_set_image_limits(ctx, 4096, 4096);

    // Query and print default chunk limits
    size_t chunk_size = 0, cache_size = 0;
    if (spng_get_chunk_limits(ctx, &chunk_size, &cache_size) == SPNG_OK) {
        std::printf("chunk_limit=%zu cache_limit=%zu\n", chunk_size, cache_size);
    }

    spng_ctx_free(ctx);
    return 0;
}
