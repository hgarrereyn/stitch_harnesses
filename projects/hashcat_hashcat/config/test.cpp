#include <cstdio>
extern "C" {
#include <hashcat/types.h>
#include <hashcat/hashcat.h>
}

static void event_cb(const u32 id, struct hashcat_ctx *ctx, const void *buf, const size_t len) {
    (void)id; (void)ctx; (void)buf; (void)len;
}

int main() {
    hashcat_ctx_t hc{}; // zero-init
    if (hashcat_init(&hc, event_cb) != 0) {
        std::printf("hashcat_init failed\n");
        return 1;
    }
    // Don't start a cracking session; just init/destroy to ensure linkage works
    hashcat_destroy(&hc);
    std::printf("hashcat library initialized and destroyed successfully.\n");
    return 0;
}
