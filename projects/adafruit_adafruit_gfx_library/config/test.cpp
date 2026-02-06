#include <Adafruit_GFX.h>
#include <stdint.h>
#include <stdio.h>

class MiniCanvas : public Adafruit_GFX {
public:
  MiniCanvas(int16_t w, int16_t h) : Adafruit_GFX(w, h) {
    buf_w = w; buf_h = h;
    buffer = new uint16_t[w * h]();
  }
  ~MiniCanvas() { delete[] buffer; }
  void drawPixel(int16_t x, int16_t y, uint16_t color) override {
    if (x < 0 || y < 0 || x >= buf_w || y >= buf_h) return;
    buffer[y * buf_w + x] = color;
  }
  // simple checksum to ensure drawing happened
  unsigned long checksum() const {
    unsigned long s = 0; for (int i=0;i<buf_w*buf_h;i++) s = (s*1315423911u) ^ buffer[i]; return s; }
private:
  int16_t buf_w, buf_h; uint16_t* buffer;
};

int main() {
  MiniCanvas c(64, 32);
  c.fillScreen(0);
  c.drawLine(0,0,63,31,0xFFFF);
  c.drawRect(5,5,20,10,0x07E0);
  c.fillCircle(40,16,8,0xF800);
  c.setCursor(0, 0);
  c.setTextSize(1);
  c.setTextColor(0xFFFF);
  c.write((uint8_t)'A');
  printf("Checksum: %lu\n", c.checksum());
  return 0;
}
