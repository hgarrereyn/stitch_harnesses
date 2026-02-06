#include <date/date.h>
#include <iostream>
#include <chrono>

int main() {
    using namespace date;
    using namespace std::chrono;

    // Construct a calendar date and compute its weekday
    year_month_day ymd{year{2020}, month{5}, day{3}}; // 2020-05-03
    weekday wd{sys_days{ymd}};

    std::cout << ymd << " " << wd << "\n";
    return 0;
}
