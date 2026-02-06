#include <iostream>
#include <grid_map_core/grid_map_core.hpp>

int main() {
  using namespace grid_map;
  GridMap map({"elevation"});
  map.setGeometry(Length(1.0, 1.0), 0.1, Position(0.0, 0.0));
  map["elevation"].setConstant(1.23);

  double sum = 0.0;
  size_t count = 0;
  for (GridMapIterator it(map); !it.isPastEnd(); ++it) {
    sum += map.at("elevation", *it);
    ++count;
  }
  std::cout << "Cells: " << count << ", Sum: " << sum << std::endl;
  return 0;
}
