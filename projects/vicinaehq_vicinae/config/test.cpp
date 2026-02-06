#include <iostream>
#include <string>
#include <filesystem>
#include "vicinae/watcher.hpp"

int main() {
  using namespace wtr; // brings watcher inline namespace
  // Create a simple file event and stringify it
  watcher::event ev{std::filesystem::path{"/tmp/test.txt"}, watcher::event::effect_type::create, watcher::event::path_type::file};
  std::string s = to<std::string>(ev);
  std::cout << s << std::endl;
  return 0;
}
