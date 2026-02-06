#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "zlib-ng.h"

int main() {
    const char* ver = zlibng_version();
    printf("zlib-ng version: %s\n", ver);

    const char* msg = "hello zlib-ng";
    size_t src_len = strlen(msg);

    size_t bound = zng_compressBound(src_len);
    unsigned char* comp = (unsigned char*)malloc(bound);
    if (!comp) return 1;
    size_t comp_len = bound;

    int r = zng_compress(comp, &comp_len, (const unsigned char*)msg, src_len);
    if (r != Z_OK) {
        printf("compress failed: %d\n", r);
        free(comp);
        return 1;
    }

    unsigned int crc = zng_crc32(0, comp, (unsigned int)comp_len);
    printf("compressed %zu -> %zu bytes, crc32=%u\n", src_len, comp_len, crc);

    free(comp);
    return 0;
}
