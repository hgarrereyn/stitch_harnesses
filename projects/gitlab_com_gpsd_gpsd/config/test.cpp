#include <cstdio>
#include <cstring>
#include <gps.h>

int main() {
    // Exercise a couple of libgps utility functions that do not need a running gpsd
    double d = earth_distance(37.4219999, -122.0840575, 48.8583701, 2.2944813); // Googleplex -> Eiffel Tower
    char tbuf[64];
    memset(tbuf, 0, sizeof(tbuf));
    now_to_iso8601(tbuf, sizeof(tbuf));

    // Basic sanity output so program runs and exits
    if (d <= 0.0) {
        printf("Distance computation failed\n");
        return 1;
    }
    printf("Now: %s\nDistance: %.2f meters\n", tbuf, d);
    return 0;
}
