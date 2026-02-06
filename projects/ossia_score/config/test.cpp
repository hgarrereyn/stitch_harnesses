#include <score/tools/Clamp.hpp>
#include <score/tools/Version.hpp>
#include <iostream>

int main(){
  int v = clamp(15, 0, 10); // should clamp to 10
  score::Version v1{1};
  score::Version v2{2};
  bool lt = v1 < v2;
  std::cout << "clamp:" << v << ", lt:" << lt << "\n";
  return 0;
}
