#include <iostream>
#include <string>
#include "src/common/base/byte_utils.h"

int main() {
  using namespace px::utils;
  uint32_t x = 0x01020304u;
  auto y = ReverseBytes(&x);
  // Expect 0x04030201
  std::cout << std::hex << y << "\n";
  // Test template for array
  char a[4] = { 'A', 'B', 'C', 'D' };
  char b[4];
  ReverseBytes(a, b);
  std::string s(b, b+4);
  std::cout << s << "\n";
  return 0;
}
