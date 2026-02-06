#include <iostream>
#include <workerd/util/small-set.h>

int main() {
  workerd::SmallSet<int> s;
  bool a1 = s.add(1);
  bool a2 = s.add(2);
  bool a3 = s.add(1); // duplicate, should be false
  bool c1 = s.contains(1);
  bool c2 = s.contains(3);
  size_t n = s.size();
  // simple sanity print so the program does something
  std::cout << "added:" << a1 << a2 << a3 << " contains:" << c1 << c2 << " size:" << n << "\n";
  return (a1 && a2 && !a3 && c1 && !c2 && n == 2) ? 0 : 1;
}
