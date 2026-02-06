#include <magic_enum/magic_enum.hpp>
#include <iostream>
#include <string>

enum class Color { RED = -10, BLUE = 0, GREEN = 10 };

int main() {
  Color c1 = Color::RED;
  // Use a few API functions to ensure headers are usable
  std::cout << magic_enum::enum_name(c1) << "\n";
  auto names = magic_enum::enum_names<Color>();
  std::cout << names.size() << "\n";
  auto values = magic_enum::enum_values<Color>();
  std::cout << static_cast<int>(values[0]) << "\n";
  // enum_cast from string
  auto maybe = magic_enum::enum_cast<Color>(std::string{"GREEN"});
  if (maybe) {
    std::cout << static_cast<int>(magic_enum::enum_integer(maybe.value())) << "\n";
  } else {
    std::cout << "cast_failed\n";
  }
  return 0;
}
