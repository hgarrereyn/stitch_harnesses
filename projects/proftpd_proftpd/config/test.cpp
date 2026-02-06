#include <iostream>
#include <proftpd/version.h>

int main() {
  std::cout << "ProFTPD version: " << PROFTPD_VERSION_TEXT << "\n";
  return 0;
}
