#include <iostream>
#include <vector>
#include "f3d/utils.h"

int main() {
  f3d::utils::string_template t("Hello {who}!");
  t.substitute({{"who", "F3D"}});
  std::string s = t.str();
  std::cout << s << std::endl;
  std::vector<std::string> vars = f3d::utils::string_template("{a}{b}").variables();
  std::cout << vars.size() << std::endl;
  return 0;
}
