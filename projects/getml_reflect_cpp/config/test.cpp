#include <iostream>
#include <string>
#include <rfl/json.hpp>
#include <rfl.hpp>

struct Person {
  std::string first_name;
  std::string last_name;
  int age;
};

int main() {
  Person homer{.first_name = "Homer", .last_name = "Simpson", .age = 45};
  std::string json = rfl::json::write(homer);
  auto parsed = rfl::json::read<Person>(json);
  if (!parsed.has_value()) {
    std::cerr << "Parse failed" << std::endl;
    return 1;
  }
  auto p = parsed.value();
  std::cout << p.first_name << " " << p.last_name << " is " << p.age << " years old." << std::endl;
  return 0;
}
