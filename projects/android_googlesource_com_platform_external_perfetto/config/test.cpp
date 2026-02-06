#include <iostream>
#include <perfetto/public/thread_utils.h>

int main() {
  PerfettoThreadId tid = PerfettoGetThreadId();
  std::cout << "Perfetto thread id: " << static_cast<long long>(tid) << "\n";
  return 0;
}
