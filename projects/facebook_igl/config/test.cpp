#include <igl/IGL.h>
#include <iostream>

int main() {
  igl::Result r; // defaults to Ok
  if (!r.isOk()) {
    std::cout << "Result not OK!\n";
    return 1;
  }
  // Use a couple of trivial API types
  igl::Color c(1.0f, 0.5f, 0.25f, 1.0f);
  std::cout << "IGL basic test ran. Color rgba: " << c.r << "," << c.g << "," << c.b << "," << c.a << "\n";
  return 0;
}
