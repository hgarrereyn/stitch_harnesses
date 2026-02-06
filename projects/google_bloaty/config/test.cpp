#include <iostream>
#include <string>
#include "range_map.h"

int main() {
  // Use a header-defined function from the library API
  std::string s = bloaty::RangeMap::EntryDebugString(0, 10, 0, "label");
  std::cout << s << "\n";
  return 0;
}
