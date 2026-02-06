#include <iostream>
#include <essentia/essentia.h>

int main() {
  essentia::init();
  std::cout << "Essentia version: " << (essentia::version ? essentia::version : "unknown") << "\n";
  if (essentia::isInitialized()) {
    std::cout << "Initialized ok\n";
  }
  essentia::shutdown();
  return 0;
}
