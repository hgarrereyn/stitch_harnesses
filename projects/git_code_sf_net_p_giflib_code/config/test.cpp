#include <gif_lib.h>
#include <cstdio>
#include <cstdlib>

int main() {
    int err = 0;
    const char* path = "/tmp/minimal.gif";
    GifFileType* gif = EGifOpenFileName(path, false, &err);
    if (!gif) {
        fprintf(stderr, "EGifOpenFileName failed: %d\n", err);
        return 1;
    }

    ColorMapObject* cmap = GifMakeMapObject(2, nullptr);
    if (!cmap) {
        fprintf(stderr, "GifMakeMapObject failed\n");
        return 1;
    }
    cmap->Colors[0].Red = 0;   cmap->Colors[0].Green = 0;   cmap->Colors[0].Blue = 0;
    cmap->Colors[1].Red = 255; cmap->Colors[1].Green = 255; cmap->Colors[1].Blue = 255;

    if (EGifPutScreenDesc(gif, 1, 1, 1, 0, cmap) == GIF_ERROR) {
        fprintf(stderr, "EGifPutScreenDesc failed\n");
        return 1;
    }
    if (EGifPutImageDesc(gif, 0, 0, 1, 1, false, nullptr) == GIF_ERROR) {
        fprintf(stderr, "EGifPutImageDesc failed\n");
        return 1;
    }

    GifPixelType line[1] = {0};
    if (EGifPutLine(gif, line, 1) == GIF_ERROR) {
        fprintf(stderr, "EGifPutLine failed\n");
        return 1;
    }

    if (EGifCloseFile(gif, &err) == GIF_ERROR) {
        fprintf(stderr, "EGifCloseFile failed: %d\n", err);
        return 1;
    }

    GifFreeMapObject(cmap);

    GifFileType* in = DGifOpenFileName(path, &err);
    if (!in) {
        fprintf(stderr, "DGifOpenFileName failed: %d\n", err);
        return 1;
    }
    if (DGifSlurp(in) == GIF_ERROR) {
        fprintf(stderr, "DGifSlurp failed\n");
        return 1;
    }
    if (DGifCloseFile(in, &err) == GIF_ERROR) {
        fprintf(stderr, "DGifCloseFile failed: %d\n", err);
        return 1;
    }

    printf("OK\n");
    return 0;
}
