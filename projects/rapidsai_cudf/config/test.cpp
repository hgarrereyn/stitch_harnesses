#include <cudf/types.hpp>
#include <iostream>

int main() {
  // Create a couple of cudf::data_type instances and compare them
  cudf::data_type t1{cudf::type_id::INT32};
  cudf::data_type t2{cudf::type_id::FLOAT64};
  std::cout << "t1 id == INT32: " << (t1.id() == cudf::type_id::INT32) << "\n";
  std::cout << "t2 id == FLOAT64: " << (t2.id() == cudf::type_id::FLOAT64) << "\n";
  std::cout << "t1 == t2: " << (t1 == t2) << "\n";
  return 0;
}
