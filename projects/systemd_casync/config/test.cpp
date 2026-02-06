#include <cstdio>
#include <cstdint>
#include <endian.h>
extern "C" {
#include "cadigest.h"
}

int main() {
    CaDigest *d = nullptr;
    if (ca_digest_new(CA_DIGEST_SHA256, &d) != 0) {
        std::printf("Failed to create digest\n");
        return 0;
    }
    const char *msg = "hello world";
    ca_digest_write(d, msg, 11);
    const unsigned char *out = (const unsigned char*)ca_digest_read(d);
    size_t sz = ca_digest_get_size(d);
    unsigned sum = 0;
    for (size_t i = 0; i < sz; ++i) sum += out[i];
    std::printf("Digest sum: %u (size=%zu)\n", sum, sz);
    ca_digest_free(d);
    return 0;
}
