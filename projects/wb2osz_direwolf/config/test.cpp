#include <cstdio>
#include <cmath>
#include <utm.h>

int main() {
    // WGS84 parameters
    double a = 6378137.0;                 // semi-major axis (meters)
    double f = 1.0 / 298.257223563;       // flattening
    long override_zone = 0;                // no override
    long err = Set_UTM_Parameters(a, f, override_zone);
    if (err != 0) {
        std::printf("Set_UTM_Parameters error: %ld\n", err);
        return 1;
    }

    // Example coordinates: Boston, MA approx 42.3601 N, -71.0589 W
    double lat_deg = 42.3601;
    double lon_deg = -71.0589;
    double lat = lat_deg * M_PI / 180.0;
    double lon = lon_deg * M_PI / 180.0;

    long zone; char hemi; double easting, northing;
    err = Convert_Geodetic_To_UTM(lat, lon, &zone, &hemi, &easting, &northing);
    if (err != 0) {
        std::printf("Convert_Geodetic_To_UTM error: %ld\n", err);
        return 1;
    }

    std::printf("Zone %ld %c, E=%.2f, N=%.2f\n", zone, hemi, easting, northing);
    return 0;
}
