#include <stdio.h>
#include <lcms2.h>

int main() {
    // Create an sRGB profile and a transform, then run a single pixel through it
    cmsHPROFILE srgb = cmsCreate_sRGBProfile();
    if (!srgb) {
        printf("Failed to create sRGB profile\n");
        return 1;
    }

    cmsHTRANSFORM xform = cmsCreateTransform(srgb, TYPE_RGB_8, srgb, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    if (!xform) {
        printf("Failed to create transform\n");
        cmsCloseProfile(srgb);
        return 1;
    }

    unsigned char in[3] = {128, 200, 30};
    unsigned char out[3] = {0, 0, 0};
    cmsDoTransform(xform, in, out, 1);

    printf("Transformed pixel: %u %u %u\n", (unsigned)out[0], (unsigned)out[1], (unsigned)out[2]);

    cmsDeleteTransform(xform);
    cmsCloseProfile(srgb);
    return 0;
}
