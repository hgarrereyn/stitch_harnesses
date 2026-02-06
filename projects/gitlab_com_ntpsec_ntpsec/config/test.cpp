#include <stdio.h>
extern "C" {
#include <ntp_calendar.h>
}

int main() {
    struct calendar cal = {0};
    if (ntpcal_get_build_date(&cal)) {
        printf("Build date: %04u-%02u-%02u %02u:%02u:%02u (weekday %u)\n",
               cal.year, cal.month, cal.monthday, cal.hour, cal.minute, cal.second, cal.weekday);
    } else {
        printf("Could not get build date\n");
    }
    // Also exercise another API: convert an NTP timestamp near epoch to Unix time
    time64_t t = ntpcal_ntp_to_time(2208988800u /* 1970-01-01 */ , 0);
    printf("Converted time64: %lld\n", (long long)t);
    return 0;
}
