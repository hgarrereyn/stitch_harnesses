#include <iostream>
#include "rawspeed/RawSpeed-API.h"

extern "C" int rawspeed_get_number_of_processor_cores() {
  return 2; // minimal implementation required by RawSpeed
}

int main() {
  using namespace rawspeed;
  iPoint2D p(3, 4);
  iRectangle2D r(p, iPoint2D(10, 20));
  auto area = r.area();
  std::cout << "Point(" << p.x << "," << p.y << ") area of rect=" << area << "\n";
  return 0;
}
