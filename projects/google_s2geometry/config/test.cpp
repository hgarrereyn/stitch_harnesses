#include <iostream>
#include "s2/s2latlng.h"
#include "s2/s2cap.h"
#include "s2/s2point.h"

int main() {
    // Define two points and a small cap around one
    S2LatLng center = S2LatLng::FromDegrees(37.4219999, -122.0840575); // Googleplex
    S2Point center_point = center.ToPoint();
    S1Angle radius = S1Angle::Degrees(1.0); // 1 degree cap
    S2Cap cap(center_point, radius);

    S2LatLng other = S2LatLng::FromDegrees(37.7749, -122.4194); // San Francisco
    bool contains_sf = cap.Contains(other.ToPoint());

    std::cout << "Cap area: " << cap.GetArea() << "\n";
    std::cout << "Contains SF: " << (contains_sf ? "yes" : "no") << "\n";
    return 0;
}
