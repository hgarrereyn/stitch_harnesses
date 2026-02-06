#include <iostream>
extern "C" {
#include "GlobalStateCleanup_fp.h"
}
int main() {
  GlobalStateCleanup();
  std::cout << "GlobalStateCleanup called successfully\n";
  return 0;
}
