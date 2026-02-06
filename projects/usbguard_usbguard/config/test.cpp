#include <usbguard/USBGuard.hpp>
#include <iostream>
int main() {
  std::string p = usbguard::getDaemonConfigPath();
  std::cout << "ConfigPathLen=" << p.size() << "\n";
  return 0;
}
