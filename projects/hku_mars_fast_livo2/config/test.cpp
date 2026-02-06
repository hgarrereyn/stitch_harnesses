#include <iostream>
#include <Eigen/Core>
#include <utils/so3_math.h>
#include <utils/types.h>

int main(){
  // Use Exp/Log from so3_math
  Eigen::Vector3d w(0.1, 0.2, -0.3);
  Eigen::Matrix3d R = Exp(w(0), w(1), w(2));
  Eigen::Vector3d v = Log(R);
  std::cout << "R(0,0)=" << R(0,0) << ", v.norm=" << v.norm() << "\n";

  // Use PCL typedefs from types.h
  PointCloudXYZI::Ptr cloud(new PointCloudXYZI());
  cloud->push_back(PointType());
  std::cout << "cloud size=" << cloud->size() << "\n";
  return 0;
}
