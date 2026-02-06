#include <fmt/base.h>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <vector>

int main() {
  fmt::print("Hello, {}!\\n", "fmt");
  std::string s = fmt::format("The answer is {}.", 42);
  auto now = std::chrono::system_clock::now();
  fmt::print("Now: {}\\n", now);
  std::vector<int> v = {1,2,3};
  fmt::print("Vector size: {}\\n", v.size());
  return s.empty();
}
