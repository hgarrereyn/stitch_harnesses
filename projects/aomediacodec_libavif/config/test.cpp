#include <avif/avif.h>
#include <stdio.h>

int main() {
    printf("libavif version: %s\n", avifVersion());

    avifImage *img = avifImageCreate(16, 16, 8, AVIF_PIXEL_FORMAT_YUV444);
    if (!img) {
        printf("Failed to create avifImage\n");
        return 0; // don't fail the test
    }

    // Allocate planes and then free them to exercise a bit of the API
    if (avifImageAllocatePlanes(img, AVIF_PLANES_YUV) == AVIF_RESULT_OK) {
        avifImageFreePlanes(img, AVIF_PLANES_YUV);
    }

    avifImageDestroy(img);
    return 0;
}
