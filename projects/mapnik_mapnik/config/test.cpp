#include <mapnik/mapnik.hpp>
#include <iostream>

int main() {
    mapnik::setup();
    std::cout << "Mapnik setup() called successfully\n";
    return 0;
}
