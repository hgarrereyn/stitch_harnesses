#include <iostream>
#include <AdaptiveCpp/hipSYCL/common/config.hpp>

int main() {
  std::cout << "AdaptiveCpp version: "
            << HIPSYCL_VERSION_MAJOR << "."
            << HIPSYCL_VERSION_MINOR << "."
            << HIPSYCL_VERSION_PATCH << "\n";
  return 0;
}
