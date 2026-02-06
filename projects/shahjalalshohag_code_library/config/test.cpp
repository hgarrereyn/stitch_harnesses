#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "code_library.hpp"

int main() {
  using namespace shah;
  long long mod = 1000000007LL;
  long long p = power_mod(2, 10, mod);
  std::cout << "pow= " << p << "\n";
  long long inv = mod_inverse(3, mod);
  std::cout << "inv3= " << inv << "\n";
  assert(inv > 0);
  std::vector<int> z = z_function("aaaa");
  std::cout << "z0= " << (z.empty()? -1 : z[0]) << ", z1= " << z[1] << "\n";
  DSU dsu(5);
  dsu.merge(1, 2);
  dsu.merge(3, 4);
  std::cout << "same12= " << dsu.same(1,2) << ", same14= " << dsu.same(1,4) << "\n";
  std::cout << "ok\n";
  return 0;
}
