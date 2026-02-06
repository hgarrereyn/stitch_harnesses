#include <vips/vips.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (VIPS_INIT(argv[0])) {
        fprintf(stderr, "vips init failed: %s\n", vips_error_buffer());
        vips_error_clear();
        return 1;
    }

    VipsImage *img = NULL;
    if (vips_black(&img, 32, 24, NULL)) {
        fprintf(stderr, "vips_black failed: %s\n", vips_error_buffer());
        vips_error_clear();
        vips_shutdown();
        return 1;
    }

    printf("libvips version: %s, image %dx%d bands=%d\n", vips_version_string(), img->Xsize, img->Ysize, img->Bands);

    g_object_unref(img);
    vips_shutdown();
    return 0;
}
