#include <iostream>
#include <h3/h3api.h>

static double deg2rad(double d) { return d * 3.14159265358979323846 / 180.0; }

int main() {
    // Statue of Liberty
    LatLng ll;
    ll.lat = deg2rad(40.689167);
    ll.lng = deg2rad(-74.044444);

    H3Index idx = 0;
    H3Error err = latLngToCell(&ll, 10, &idx);
    if (err != E_SUCCESS || idx == H3_NULL) {
        std::cout << "latLngToCell failed with error: " << (unsigned)err << "\n";
        return 0;
    }

    LatLng center{};
    err = cellToLatLng(idx, &center);
    if (err != E_SUCCESS) {
        std::cout << "cellToLatLng failed with error: " << (unsigned)err << "\n";
        return 0;
    }

    std::cout << "Index: " << idx << "\n";
    std::cout << "Center (rad): lat=" << center.lat << ", lng=" << center.lng << "\n";
    return 0;
}
