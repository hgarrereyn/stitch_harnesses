#include <iostream>
#include "dali/core/dali_data_type.h"

int main() {
  const char* name = daliDataTypeName(DALI_FLOAT);
  if (!name) return 1;
  std::cout << "DALI data type name: " << name << "\n";
  std::cout << "Is floating point? " << (daliDataTypeIsFloatingPoint(DALI_FLOAT) ? "yes" : "no") << "\n";
  std::cout << "Is integral? " << (daliDataTypeIsIntegral(DALI_FLOAT) ? "yes" : "no") << "\n";
  return 0;
}
