#include <iostream>
#include "base/operators.h"

int main() {
  // Use only enum values to avoid requiring non-header definitions.
  cel::OperatorId op = cel::OperatorId::kAdd;
  std::cout << "OperatorId kAdd value: " << static_cast<int>(op) << "\n";
  // Ensure basic types are accessible
  cel::Arity ar = cel::Arity::kBinary;
  std::cout << "Arity kBinary value: " << static_cast<int>(ar) << "\n";
  return 0;
}
