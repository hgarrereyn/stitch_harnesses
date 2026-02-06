#include <iostream>
#include <tink/version.h>

int main() {
  std::cout << "Tink version: " << crypto::tink::Version::kTinkVersion << std::endl;
  return 0;
}
