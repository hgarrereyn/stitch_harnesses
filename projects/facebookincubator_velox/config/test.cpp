#include <iostream>
#include <vector>
#include "velox/type/Tree.h"

using namespace facebook::velox;

struct IntTree : public Tree<int> {
  std::vector<int> v{4,5,6};
  size_type size() const override { return v.size(); }
  const_reference childAt(size_type idx) const override { return v[idx]; }
};

int main() {
  IntTree t;
  long sum = 0;
  for (auto it = t.cbegin(); !(it == t.cend()); it++) {
    sum += *it;
  }
  std::cout << "sum=" << sum << "\n";
  return sum == 15 ? 0 : 1;
}
