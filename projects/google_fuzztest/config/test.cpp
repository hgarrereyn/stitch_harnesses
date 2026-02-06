#include <iostream>
#include <fuzztest/fuzztest.h>

int main() {
  auto d = fuzztest::Positive<int>();
  (void)d;
  std::cout << "FuzzTest headers available." << std::endl;
  return 0;
}
