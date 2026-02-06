#include <cstdio>
#include <cstring>
#include <bearssl.h>

int main() {
    const char *msg = "hello world";
    br_sha256_context ctx;
    br_sha256_init(&ctx);
    br_sha256_update(&ctx, msg, strlen(msg));
    unsigned char out[32];
    br_sha256_out(&ctx, out);
    // Print first 4 bytes as a quick sanity check
    std::printf("SHA256 first bytes: %02x %02x %02x %02x\n", out[0], out[1], out[2], out[3]);
    return 0;
}
