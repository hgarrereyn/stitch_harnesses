#include <iostream>
#include <Eigen/Core>
#include <igl/avg_edge_length.h>

int main() {
  // Simple single triangle mesh
  Eigen::Matrix<double,3,3> V;
  V << 0.0, 0.0, 0.0,
       1.0, 0.0, 0.0,
       0.0, 1.0, 0.0;
  Eigen::Matrix<int,1,3> F;
  F << 0,1,2;

  double a = igl::avg_edge_length(V, F);
  std::cout << "Avg edge length: " << a << "\n";
  return 0;
}
