#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "flv-header.h"

int main() {
    uint8_t buf[16] = {0};
    int n = flv_header_write(1, 1, buf, sizeof(buf));
    if (n <= 0) {
        printf("flv_header_write failed: %d\n", n);
        return 0;
    }
    struct flv_header_t hdr; memset(&hdr, 0, sizeof(hdr));
    int r = flv_header_read(&hdr, buf, (size_t)n);
    printf("flv_header_read ret=%d, ver=%u, audio=%u, video=%u, offset=%u\n",
           r, hdr.version, hdr.audio, hdr.video, (unsigned)hdr.offset);
    return 0;
}
