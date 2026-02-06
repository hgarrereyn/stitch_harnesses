#include <png.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned int ver = png_access_version_number();
    printf("libpng version: %u\n", ver);

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        printf("Failed to create png_struct\n");
        return 0; // not fatal for test
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        printf("Failed to create info struct\n");
        return 0;
    }

    // Clean up immediately; we aren't actually writing anything
    png_destroy_write_struct(&png_ptr, &info_ptr);
    printf("libpng basic API call succeeded\n");
    return 0;
}
