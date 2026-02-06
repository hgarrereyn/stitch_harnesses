#include <tiffio.h>
#include <cstdio>
#include <cstdint>

int main() {
    const char* fname = "/tmp/libtiff_test.tif";
    TIFF* t = TIFFOpen(fname, "w");
    if (!t) {
        std::fprintf(stderr, "Failed to open TIFF for writing\n");
        return 1;
    }
    uint32_t width = 1, height = 1;
    TIFFSetField(t, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(t, TIFFTAG_IMAGELENGTH, height);
    TIFFSetField(t, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(t, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(t, TIFFTAG_ROWSPERSTRIP, 1);
    TIFFSetField(t, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
    TIFFSetField(t, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    TIFFSetField(t, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

    uint8_t pixel = 127;
    if (TIFFWriteScanline(t, &pixel, 0, 0) != 1) {
        std::fprintf(stderr, "Failed to write scanline\n");
        TIFFClose(t);
        return 1;
    }
    TIFFClose(t);

    // Read back and verify
    t = TIFFOpen(fname, "r");
    if (!t) {
        std::fprintf(stderr, "Failed to open TIFF for reading\n");
        return 1;
    }
    uint32_t rwidth = 0, rheight = 0;
    TIFFGetField(t, TIFFTAG_IMAGEWIDTH, &rwidth);
    TIFFGetField(t, TIFFTAG_IMAGELENGTH, &rheight);
    if (rwidth != width || rheight != height) {
        std::fprintf(stderr, "Dimension mismatch\n");
        TIFFClose(t);
        return 1;
    }
    uint8_t in = 0;
    if (TIFFReadScanline(t, &in, 0, 0) != 1) {
        std::fprintf(stderr, "Failed to read scanline\n");
        TIFFClose(t);
        return 1;
    }
    TIFFClose(t);
    if (in != pixel) {
        std::fprintf(stderr, "Pixel mismatch\n");
        return 1;
    }
    std::printf("OK\n");
    return 0;
}
