#include <iostream>
#include <perfetto/base/time.h>

int main() {
  perfetto::base::InitializeTime();
  auto t = perfetto::base::GetWallTimeNs();
  std::cout << "Perfetto wall time ns: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(t).count()
            << "\n";
  return 0;
}
