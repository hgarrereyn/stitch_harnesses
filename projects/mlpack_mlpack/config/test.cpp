#include <iostream>
#include <mlpack/core.hpp>
#include <mlpack/core/math/range.hpp>

int main() {
  // Simple use of a small part of mlpack API: Range operations.
  mlpack::Range r(0.0, 10.0);
  bool c5 = r.Contains(5.0);
  bool c15 = r.Contains(15.0);
  auto width = r.Width();
  std::cout << "Contains 5: " << c5 << " Contains 15: " << c15 << " Width: " << width << "\n";
  return 0;
}
