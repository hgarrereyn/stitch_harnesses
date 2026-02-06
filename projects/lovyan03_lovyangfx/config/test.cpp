#include <cstdio>
#define LGFX_SDL
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

int main() {
  // Use only in-memory sprite operations to avoid opening a real window.
  LGFX lcd; // Comes from AUTODETECT (SDL)
  lgfx::v1::LGFX_Sprite sprite(&lcd);
  sprite.setColorDepth(16);
  sprite.createSprite(32, 32);
  for (int y = 0; y < 32; ++y) {
    for (int x = 0; x < 32; ++x) {
      uint16_t c = ((x & 0x1F) << 11) | ((y & 0x3F) << 5) | (x ^ y);
      sprite.drawPixel(x, y, c);
    }
  }
  // Read back a pixel and print to confirm things ran
  uint32_t p = sprite.readPixel(10, 10);
  std::printf("pixel=%u\n", (unsigned)p);
  sprite.deleteSprite();
  return 0;
}
