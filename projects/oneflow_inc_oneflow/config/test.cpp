#include <iostream>
#include <string>
#include <oneflow/maybe/maybe.h>

int main() {
  using namespace oneflow::maybe;

  using ErrT = simple::NoStackError<std::string>;

  // Create a successful Maybe<int, ErrT>
  Maybe<int, ErrT> ok_maybe(Ok, 42);
  int v = CHECK_JUST(ok_maybe);
  std::cout << "Value: " << v << "\n";

  // Create an error Maybe<int, ErrT>
  Maybe<int, ErrT> bad_maybe(InPlaceError, std::string("something went wrong"));
  if (bad_maybe.IsOk()) {
    std::cerr << "Expected error but got ok\n";
    return 1;
  }
  std::cout << "Error message size: " << bad_maybe.GetError().size() << "\n";

  // Bind style usage
  auto plus_one = [](int x) { return Maybe<int, ErrT>(Ok, x + 1); };
  auto res = ok_maybe.Bind(plus_one);
  int rv = CHECK_JUST(res);
  if (rv != 43) {
    std::cerr << "Bind failed\n";
    return 1;
  }
  std::cout << "Bind Value: " << rv << "\n";
  return 0;
}
