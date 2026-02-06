#include <iostream>
#include <vector>

#include "common/geometry/vec2d.h"
#include "common/geometry/curve/cubic_spline_curve.h"
#include "common/geometry/point.h"
#include "common/util/log.h"

// Provide the definition for the declared global logger initializer to satisfy linkage
rmp::common::util::LoggerInitializer logger_initializer;

int main() {
  using namespace rmp::common::geometry;

  // Simple Vec2d usage
  Vec2d v1(3.0, 4.0);
  std::cout << "v1 length: " << v1.length() << "\n";

  // Use cubic spline to generate a simple path between two poses
  CubicSplineCurve spline(0.1);
  Point3d start(0.0, 0.0, 0.0);
  Point3d goal(1.0, 1.0, 0.0);
  Points3d path;
  bool ok = spline.generation(start, goal, path);
  std::cout << "spline generation: " << (ok ? "ok" : "fail") << ", points: " << path.size() << "\n";

  // Print first few points
  size_t n = std::min<size_t>(path.size(), 3);
  for (size_t i = 0; i < n; ++i) {
    std::cout << "pt" << i << ": (" << path[i].x() << ", " << path[i].y() << ", " << path[i].theta() << ")\n";
  }

  return 0;
}
