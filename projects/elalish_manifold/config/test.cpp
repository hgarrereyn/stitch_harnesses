#include <iostream>
#include "manifold/manifold.h"

int main() {
  using namespace manifold;
  Manifold m = Manifold::Sphere(1.0, 24);
  if (m.Status() != Manifold::Error::NoError) {
    std::cerr << "Manifold creation failed\n";
    return 1;
  }
  double vol = m.Volume();
  double area = m.SurfaceArea();
  auto bbox = m.BoundingBox();
  std::cout << "Volume: " << vol << "\n";
  std::cout << "SurfaceArea: " << area << "\n";
  std::cout << "BBox min: (" << bbox.min.x << ", " << bbox.min.y << ", " << bbox.min.z << ")\n";
  std::cout << "BBox max: (" << bbox.max.x << ", " << bbox.max.y << ", " << bbox.max.z << ")\n";
  Manifold m2 = m.Translate({1.0, 2.0, 3.0}).Scale({2.0, 2.0, 2.0});
  std::cout << "Transformed Volume: " << m2.Volume() << "\n";
  return 0;
}
