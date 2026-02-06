#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include "jpegoptim.h"

int main() {
    // Set up a minimal JPEG compression to an in-memory buffer using jpegoptim's custom destination manager
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    size_t outsize = 1024; // initial buffer size
    unsigned char* outbuf = (unsigned char*)malloc(outsize);
    if (!outbuf) return 1;
    jpeg_memory_dest(&cinfo, &outbuf, &outsize, 4096);

    cinfo.image_width = 1;
    cinfo.image_height = 1;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);

    jpeg_start_compress(&cinfo, TRUE);
    JSAMPLE pixel[3] = {0, 0, 0};
    JSAMPROW row[1];
    row[0] = pixel;
    jpeg_write_scanlines(&cinfo, row, 1);
    jpeg_finish_compress(&cinfo);

    // Clean up
    jpeg_destroy_compress(&cinfo);
    free(outbuf);

    printf("jpegoptim library linked and ran successfully.\n");
    return 0;
}
