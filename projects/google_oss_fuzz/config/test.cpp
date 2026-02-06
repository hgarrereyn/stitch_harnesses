#include <iostream>
#include <string>
#include <oss_fuzz_dummy.h>
int main() {
  std::string v = ossfuzz::version();
  std::cout << "Dummy lib says: " << v << "\n";
  return 0;
}
