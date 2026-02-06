#include <ceres/ceres.h>
#include <iostream>

// A simple 1D cost function: residual = 10 - x
struct SimpleResidual {
  template <typename T>
  bool operator()(const T* const x, T* residual) const {
    residual[0] = T(10.0) - x[0];
    return true;
  }
};

int main() {
  double x = 0.5; // initial value

  ceres::Problem problem;
  ceres::CostFunction* cost_function =
      new ceres::AutoDiffCostFunction<SimpleResidual, 1, 1>(new SimpleResidual);
  problem.AddResidualBlock(cost_function, nullptr, &x);

  ceres::Solver::Options options;
  options.max_num_iterations = 50;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = false;

  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);

  std::cout << "Initial x: 0.5, final x: " << x << "\n";
  // Ensure program does something deterministic
  if (x <= 9.9) return 1;
  return 0;
}
