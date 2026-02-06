#include <iostream>
#include <memory>
#include <fcl/fcl.h>

int main() {
  using S = double;
  // Create two spheres of radius 1
  std::shared_ptr<fcl::Sphered> s1(new fcl::Sphered(1.0));
  std::shared_ptr<fcl::Sphered> s2(new fcl::Sphered(1.0));

  // Identity transforms
  fcl::Transform3<S> tf1 = fcl::Transform3<S>::Identity();
  fcl::Transform3<S> tf2 = fcl::Transform3<S>::Identity();

  // Place the second sphere 3 units away on x axis (no collision)
  tf2.translation() = Eigen::Matrix<S,3,1>(3.0, 0.0, 0.0);

  fcl::CollisionObject<S> o1(s1, tf1);
  fcl::CollisionObject<S> o2(s2, tf2);

  fcl::CollisionRequest<S> request; // default
  fcl::CollisionResult<S> result;

  std::size_t num = fcl::collide(&o1, &o2, request, result);

  std::cout << "Contacts (expected 0): " << num << "\n";

  // Move closer to make them collide
  tf2.translation() = Eigen::Matrix<S,3,1>(1.5, 0.0, 0.0);
  o2.setTransform(tf2);
  result.clear();
  num = fcl::collide(&o1, &o2, request, result);
  std::cout << "Contacts after move (expected >0): " << num << "\n";
  return 0;
}
