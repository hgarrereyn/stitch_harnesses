#include <iostream>
#include <chrono>
#include "cctz/civil_time.h"
#include "cctz/time_zone.h"

int main() {
  cctz::time_zone utc = cctz::utc_time_zone();
  auto now = std::chrono::time_point_cast<cctz::seconds>(
      std::chrono::system_clock::now());
  std::string now_str = cctz::format("%Y-%m-%d %H:%M:%S %Ez", now, utc);
  std::cout << "Now UTC: " << now_str << "\n";

  cctz::civil_second cs(2000, 1, 1, 0, 0, 0);
  auto tp = cctz::convert(cs, utc);
  auto al = utc.lookup(tp);
  std::cout << "Y2K UTC: " << cctz::format("%Y-%m-%d %H:%M:%S %Ez", tp, utc)
            << ", weekday=" << static_cast<int>(cctz::get_weekday(al.cs))
            << "\n";

  cctz::time_zone plus2 = cctz::fixed_time_zone(std::chrono::hours(2));
  std::cout << cctz::format("%Y-%m-%d %H:%M:%S %Ez", tp, plus2) << "\n";
  return 0;
}
