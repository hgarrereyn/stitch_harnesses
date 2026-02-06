#include <deal.II/base/point.h>
#include <deal.II/base/utilities.h>
#include <iostream>

int main() {
  using namespace dealii;
  Point<2> p1(1.0, 2.0);
  Point<2> p2(4.0, 6.0);
  double dist = p1.distance(p2);
  std::cout << "Distance: " << dist << "\n";

  // Use a simple Utilities function
  std::string s = Utilities::int_to_string(42, 3);
  std::cout << "Padded number: " << s << "\n";
  return 0;
}
