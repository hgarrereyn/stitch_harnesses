#include <oatpp/Environment.hpp>
#include <oatpp/Types.hpp>
#include <iostream>

int main() {
  oatpp::Environment::init();

  oatpp::String s = "hello, oatpp";
  if(s) {
    std::cout << "String value: " << s->c_str() << std::endl;
  }

  std::cout << "OATPP_VERSION=" << OATPP_VERSION << std::endl;

  oatpp::Environment::destroy();
  return 0;
}
