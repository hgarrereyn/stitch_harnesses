#include <Eigen/Dense>
#include <iostream>

int main() {
  Eigen::Matrix2d A;
  A << 1.0, 2.0,
       3.0, 4.0;
  Eigen::Vector2d b(5.0, 6.0);
  Eigen::Vector2d x = A.colPivHouseholderQr().solve(b);
  // Compute residual
  double r = (A*x - b).norm();
  std::cout << "Residual: " << r << "\n";
  // Do a small operation to ensure templates instantiate
  Eigen::MatrixXd M = Eigen::MatrixXd::Random(3,3);
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(M.transpose()*M);
  std::cout << "First eigenvalue: " << es.eigenvalues()[0] << "\n";
  return 0;
}
