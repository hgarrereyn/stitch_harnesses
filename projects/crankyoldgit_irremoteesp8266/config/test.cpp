#include <iostream>
#include "IRremoteESP8266.h"
#include "IRutils.h"
#include "IRsend.h"

int main() {
  std::cout << "IRremoteESP8266 version: " << _IRREMOTEESP8266_VERSION_STR << "\n";
  float c = 25.0f;
  float f = celsiusToFahrenheit(c);
  std::cout << c << " C = " << f << " F\n";
  std::cout << "Default duty: " << (int)kDutyDefault << "%\n";
  return 0;
}
