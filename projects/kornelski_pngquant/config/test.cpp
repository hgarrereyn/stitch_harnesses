#include <stdio.h>
extern "C" {
#include "rwpng.h"
}

int main() {
    // Print version info from libpng via rwpng helper
    rwpng_version_info(stdout);

    // Create and zero-initialize a png24_image and png8_image to ensure structs are accessible
    png24_image img24 = {0};
    png8_image img8 = {0};
    (void)img24; (void)img8;

    // Nothing else to do; just return success
    return 0;
}
