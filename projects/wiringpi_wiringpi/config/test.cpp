#include <wiringPi.h>
#include <iostream>
int main() {
    std::cout << "WiringPi constants: WPI_MODE_PINS=" << WPI_MODE_PINS
              << ", INPUT=" << INPUT << ", OUTPUT=" << OUTPUT << "\n";
    return 0;
}
