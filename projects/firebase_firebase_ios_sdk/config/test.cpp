#include <firebase/firestore/geo_point.h>
#include <iostream>

int main() {
    firebase::firestore::GeoPoint gp; // default constructed
    std::cout << "GeoPoint: (" << gp.latitude() << ", " << gp.longitude() << ")\n";
    return 0;
}
