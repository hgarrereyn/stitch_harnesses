#include <iostream>
#include <rubinius/util/timer.hpp>

int main() {
  using rubinius::utilities::timer::Timer;

  Timer t;
  t.set(1);
  t.cancel();
  int ticks = t.wait_for_tick();
  t.clear();

  std::cout << "Timer ticked: " << ticks << " times\n";
  return 0;
}
