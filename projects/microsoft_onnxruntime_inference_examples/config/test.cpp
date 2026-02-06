#include <iostream>
#include "providers.h"

int main() {
  // providers.h conditionally includes provider factory headers based on defines.
  // With no EP defines set, it should compile to a no-op include and run fine.
  std::cout << "ONNX Runtime providers header included successfully.\n";
  return 0;
}
