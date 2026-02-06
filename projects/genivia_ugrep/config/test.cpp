#include <reflex/matcher.h>
#include <reflex/input.h>
#include <iostream>

int main() {
  reflex::Matcher matcher("hello", reflex::Input("say hello world"));
  if (matcher.find()) {
    std::cout << "Found: " << matcher.text() << "\n";
  } else {
    std::cout << "Not found\n";
  }
  return 0;
}
