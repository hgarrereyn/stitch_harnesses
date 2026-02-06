#include <turbojpeg.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

int main() {
  // Create a simple 2x2 RGB image: red, green, blue, white
  const int width = 2, height = 2, pixelSize = 3;
  unsigned char rgb[width * height * pixelSize] = {
      255, 0, 0,    0, 255, 0,
      0, 0, 255,    255, 255, 255
  };

  tjhandle comp = tjInitCompress();
  if (!comp) {
    std::fprintf(stderr, "tjInitCompress failed: %s\n", tjGetErrorStr());
    return 1;
  }

  unsigned char* jpegBuf = nullptr; // will be allocated by TurboJPEG
  unsigned long jpegSize = 0;
  int subsamp = TJSAMP_420; // chroma subsampling
  int flags = 0;

  if (tjCompress2(comp, rgb, width, 0, height, TJPF_RGB,
                  &jpegBuf, &jpegSize, subsamp, 75, flags) != 0) {
    std::fprintf(stderr, "tjCompress2 failed: %s\n", tjGetErrorStr2(comp));
    tjDestroy(comp);
    return 1;
  }
  tjDestroy(comp);

  tjhandle decomp = tjInitDecompress();
  if (!decomp) {
    std::fprintf(stderr, "tjInitDecompress failed: %s\n", tjGetErrorStr());
    tjFree(jpegBuf);
    return 1;
  }

  int outW = 0, outH = 0, outSubsamp = 0, outColorspace = 0;
  if (tjDecompressHeader3(decomp, jpegBuf, jpegSize, &outW, &outH, &outSubsamp, &outColorspace) != 0) {
    std::fprintf(stderr, "tjDecompressHeader3 failed: %s\n", tjGetErrorStr2(decomp));
    tjDestroy(decomp);
    tjFree(jpegBuf);
    return 1;
  }

  std::vector<unsigned char> outBuf(width * height * pixelSize);
  if (tjDecompress2(decomp, jpegBuf, jpegSize, outBuf.data(), width, 0, height, TJPF_RGB, 0) != 0) {
    std::fprintf(stderr, "tjDecompress2 failed: %s\n", tjGetErrorStr2(decomp));
    tjDestroy(decomp);
    tjFree(jpegBuf);
    return 1;
  }

  tjDestroy(decomp);
  tjFree(jpegBuf);

  // Simple verification: print first pixel values
  std::printf("%d %d %d\n", outBuf[0], outBuf[1], outBuf[2]);
  return 0;
}
