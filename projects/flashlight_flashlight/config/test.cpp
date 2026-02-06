#include <flashlight/fl/flashlight.h>
#include <iostream>

int main() {
  try {
    fl::init();
    std::cout << "flashlight initialized" << std::endl;
  } catch (const std::exception& ex) {
    std::cout << "exception: " << ex.what() << std::endl;
  }
  return 0;
}
