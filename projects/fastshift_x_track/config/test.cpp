#include <cstdio>
#include <cstdint>
#include <XTrack/Time.h>

extern "C" uint32_t lv_tick_get(void) { return 0; }

int main() {
    tmElements_t tm{};
    tm.Year = CalendarYrToTm(2021); // years since 1970
    tm.Month = 12; // December
    tm.Day = 31;   // 31st
    tm.Hour = 23;
    tm.Minute = 59;
    tm.Second = 30;

    time_t t = makeTime(tm);

    std::printf("Year: %d\n", year(t));
    std::printf("Month: %d\n", month(t));
    std::printf("Day: %d\n", day(t));
    std::printf("Hour(24h): %d\n", hour(t));
    std::printf("Minute: %d\n", minute(t));
    std::printf("Second: %d\n", second(t));

    std::printf("Month name: %s\n", monthStr(month(t)));
    std::printf("Weekday short: %s\n", dayShortStr(weekday(t)));
    return 0;
}
