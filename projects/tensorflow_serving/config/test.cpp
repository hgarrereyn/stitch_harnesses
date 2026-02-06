#include <iostream>
#include <string>
#include "tensorflow_serving/util/any_ptr.h"
#include "tensorflow_serving/util/executor.h"

using namespace tensorflow::serving;

// A simple concrete executor that runs functions inline.
class SimpleExecutor : public Executor {
 public:
  void Schedule(std::function<void()> fn) override { fn(); }
};

int main() {
  // Test AnyPtr with int
  int value = 42;
  AnyPtr p_int(&value);
  if (p_int.get<int>() != nullptr) {
    std::cout << "Int: " << *p_int.get<int>() << "\n";
  }

  // Test AnyPtr with std::string
  std::string s = "hello";
  AnyPtr p_str(&s);
  if (p_str.get<std::string>() != nullptr) {
    std::cout << "String: " << *p_str.get<std::string>() << "\n";
  }

  // Test Executor
  SimpleExecutor ex;
  int ran = 0;
  ex.Schedule([&](){ ran = 1; });
  std::cout << "Executor ran: " << ran << "\n";
  return 0;
}
