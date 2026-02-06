#include <iostream>
#include <string>
#include "lib/hash_func/murmur_hash.h"

int main() {
  const std::string s = "hello oceanbase";
  uint64_t h = oceanbase::common::murmurhash(s.data(), static_cast<int32_t>(s.size()), 0x12345678ULL);
  std::cout << "hash(" << s << ") = " << h << "\n";
  return 0;
}
