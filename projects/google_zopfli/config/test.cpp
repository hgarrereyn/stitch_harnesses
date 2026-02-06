#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zopfli.h"

int main() {
    const char* msg = "Hello, Zopfli! This is a small test input.";
    size_t in_size = strlen(msg);

    ZopfliOptions opts;
    ZopfliInitOptions(&opts);
    opts.numiterations = 2; // keep it reasonably fast
    opts.blocksplitting = 1;

    unsigned char* out = NULL;
    size_t outsize = 0;

    ZopfliCompress(&opts, ZOPFLI_FORMAT_ZLIB, (const unsigned char*)msg, in_size, &out, &outsize);

    if (!out) {
        fprintf(stderr, "Compression failed\n");
        return 1;
    }

    printf("Compressed %zu bytes to %zu bytes\n", in_size, outsize);

    free(out);
    return 0;
}
