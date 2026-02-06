#include <iostream>
#include <string>
#include "/fuzz/install/include/ccls/utils.hh"
#include "/fuzz/install/include/ccls/serializer.hh"

int main() {
  std::size_t seed = 0;
  ccls::hash_combine(seed, 1, 2, 3);
  ccls::BinaryWriter bw;
  bw.varInt(-42);
  bw.string("hello", 5);
  std::string out = bw.take();
  std::cout << "seed=" << seed << ", out_size=" << out.size() << "\n";
  return 0;
}
