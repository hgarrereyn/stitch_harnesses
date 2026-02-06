#include <vector>
#include <string>
#include <iostream>
#include <lodepng.h>

int main() {
  // Create a simple 2x2 RGBA image: red, green, blue, white
  unsigned w = 2, h = 2;
  std::vector<unsigned char> image = {
    255, 0,   0,   255,   // red
    0,   255, 0,   255,   // green
    0,   0,   255, 255,   // blue
    255, 255, 255, 255    // white
  };

  // Encode to PNG in memory
  std::vector<unsigned char> png;
  unsigned err = lodepng::encode(png, image, w, h);
  if (err) {
    std::cerr << "encode error: " << err << " - " << lodepng_error_text(err) << "\n";
    return 1;
  }

  // Decode back to raw pixels
  std::vector<unsigned char> decoded;
  unsigned dw, dh;
  err = lodepng::decode(decoded, dw, dh, png);
  if (err) {
    std::cerr << "decode error: " << err << " - " << lodepng_error_text(err) << "\n";
    return 1;
  }

  if (dw != w || dh != h || decoded.size() != image.size()) {
    std::cerr << "size mismatch" << "\n";
    return 1;
  }
  // Simple check of one pixel
  if (decoded[0] != 255 || decoded[1] != 0 || decoded[2] != 0 || decoded[3] != 255) {
    std::cerr << "pixel mismatch" << "\n";
    return 1;
  }

  std::cout << "LodePNG encode/decode OK, PNG bytes: " << png.size() << "\n";
  return 0;
}
