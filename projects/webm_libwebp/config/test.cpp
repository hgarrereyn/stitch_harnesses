#include <cstdio>
#include <cstdlib>
#include <vector>
#include <webp/encode.h>
#include <webp/decode.h>

int main() {
  const int width = 2, height = 2;
  std::vector<uint8_t> rgba(width * height * 4);
  uint8_t colors[4][4] = {
      {255, 0, 0, 255},
      {0, 255, 0, 255},
      {0, 0, 255, 255},
      {255, 255, 0, 255}
  };
  for (int i = 0; i < 4; ++i) {
    for (int c = 0; c < 4; ++c) rgba[i * 4 + c] = colors[i][c];
  }

  uint8_t* webp_data = nullptr;
  size_t webp_size = WebPEncodeRGBA(rgba.data(), width, height, width * 4, 75.0f, &webp_data);
  if (webp_size == 0 || webp_data == nullptr) {
    std::fprintf(stderr, "WebP encoding failed\n");
    return 1;
  }

  std::vector<uint8_t> out_rgba(width * height * 4, 0);
  if (!WebPDecodeRGBAInto(webp_data, webp_size, out_rgba.data(), out_rgba.size(), width * 4)) {
    std::fprintf(stderr, "WebP decoding failed\n");
    WebPFree(webp_data);
    return 1;
  }

  int ok = 1;
  for (int i = 0; i < width * height; ++i) {
    if (out_rgba[i * 4 + 3] != 255) { ok = 0; break; }
  }

  WebPFree(webp_data);
  std::printf("OK %zu bytes\n", webp_size);
  return ok ? 0 : 2;
}
