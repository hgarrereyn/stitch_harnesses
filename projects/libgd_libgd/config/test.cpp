#include <gd.h>
#include <stdio.h>

int main() {
    // Create a simple 10x10 truecolor image
    gdImagePtr im = gdImageCreateTrueColor(10, 10);
    if (!im) {
        printf("Failed to create image\n");
        return 1;
    }

    // Allocate a color and draw a pixel
    int red = gdTrueColor(255, 0, 0);
    gdImageSetPixel(im, 5, 5, red);

    // Query a pixel to ensure API works
    int px = gdImageGetTrueColorPixel(im, 5, 5);
    printf("Pixel value: %d\n", px);

    // Clean up
    gdImageDestroy(im);
    return 0;
}
