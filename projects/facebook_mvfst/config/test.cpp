#include <quic/common/third-party/optional.h>
#include <iostream>

int main() {
  quic::detail::tiny::optional<int> opt;
  if (!opt.has_value()) {
    opt = 42;
  }
  std::cout << "optional value: " << *opt << "\n";
  return 0;
}
