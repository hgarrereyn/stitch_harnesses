#include <MagickWand/MagickWand.h>
#include <cstdio>

int main() {
  MagickWandGenesis();

  PixelWand* pixel = NewPixelWand();
  PixelSetColor(pixel, "red");

  MagickWand* wand = NewMagickWand();
  if (MagickNewImage(wand, 16, 16, pixel) == MagickFalse) {
    fprintf(stderr, "Failed to create image\n");
    return 1;
  }

  // Ensure an internal format is selected that needs no external delegate.
  if (MagickSetImageFormat(wand, "MIFF") == MagickFalse) {
    fprintf(stderr, "Failed to set image format\n");
    return 1;
  }

  size_t length = 0;
  unsigned char* blob = MagickGetImageBlob(wand, &length);
  if (blob == nullptr || length == 0) {
    fprintf(stderr, "Failed to get image blob\n");
    return 1;
  }
  // Print a small message to ensure program executed
  printf("Image blob size: %zu\n", length);

  MagickRelinquishMemory(blob);
  DestroyMagickWand(wand);
  DestroyPixelWand(pixel);
  MagickWandTerminus();
  return 0;
}
