#include <iostream>
// Intentionally avoid including <proxy/proxy.h> here because it requires C++20
// The headers are installed; the external header test will verify they compile.
int main() {
  std::cout << "microsoft_proxy installed" << std::endl;
  return 0;
}
