#include <cstdint>
#include <iostream>
#include "source/common/common/byte_order.h"

int main() {
  using namespace std;
  // Test conversion to/from little/big endian for a 32-bit value.
  uint32_t x = 0x12345678u;
  auto le = toEndianness<ByteOrder::LittleEndian>(x);
  auto be = toEndianness<ByteOrder::BigEndian>(x);
  auto x_from_le = fromEndianness<ByteOrder::LittleEndian>(le);
  auto x_from_be = fromEndianness<ByteOrder::BigEndian>(be);

  if (x != x_from_le || x != x_from_be) {
    std::cerr << "Endian conversion failed" << std::endl;
    return 1;
  }
  std::cout << std::hex << le << " " << be << "\n";
  return 0;
}
