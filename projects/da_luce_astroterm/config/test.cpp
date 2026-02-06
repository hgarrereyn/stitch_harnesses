#include <iostream>
#include <ctime>
extern "C" {
#include "astro.h"
}

int main() {
    // Compute Earth rotation angle and GMST for a known date
    std::tm t{};
    t.tm_year = 125; // years since 1900 -> 2025
    t.tm_mon = 0;    // January
    t.tm_mday = 1;   // 1st
    t.tm_hour = 0; t.tm_min = 0; t.tm_sec = 0; // 00:00:00

    double jd = datetime_to_julian_date(&t);
    double era = earth_rotation_angle_rad(jd);
    double gmst = greenwich_mean_sidereal_time_rad(jd);

    // Basic sanity checks
    if (!(jd > 2400000.0)) return 1;
    if (!(era >= 0.0 && era <= 2*3.141592653589793)) return 2;

    std::cout << "JD=" << jd << ", ERA(rad)=" << era << ", GMST(rad)=" << gmst << std::endl;
    return 0;
}
