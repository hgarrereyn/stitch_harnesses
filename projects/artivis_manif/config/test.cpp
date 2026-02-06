#include <iostream>
#include <Eigen/Dense>
#include <manif/manif.h>

int main() {
    using namespace manif;

    SE3d X = SE3d::Random();
    SE3Tangentd w = SE3Tangentd::Random();

    SE3d Y = X.plus(w);
    auto t = Y.minus(X);

    Eigen::Vector3d v(1.0, 2.0, 3.0);
    Eigen::Vector3d v2 = Y.act(v);

    std::cout << "DoF: " << SE3d::DoF << ", dim: " << SE3d::Dim << "\n";
    std::cout << "t norm: " << t.squaredWeightedNorm() << "\n";
    std::cout << "v2: " << v2.transpose() << "\n";
    return 0;
}
