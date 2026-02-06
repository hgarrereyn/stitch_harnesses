#include <iostream>
#include <pinocchio/fwd.hpp>
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>
#include <pinocchio/multibody/joint/joint-revolute.hpp>
#include <pinocchio/spatial/se3.hpp>
#include <pinocchio/spatial/inertia.hpp>
#include <pinocchio/algorithm/kinematics.hpp>

int main() {
  using namespace pinocchio;

  Model model;
  JointModelRX joint_rx;
  Model::JointIndex idx = model.addJoint(model.getJointId("universe"), joint_rx, SE3::Identity(), "rx_joint");
  model.appendBodyToJoint(idx, Inertia::Random(), SE3::Identity());

  Data data(model);

  Eigen::VectorXd q = Eigen::VectorXd::Zero(model.nq);
  Eigen::VectorXd v = Eigen::VectorXd::Zero(model.nv);

  forwardKinematics(model, data, q, v);

  std::cout << "Model nq: " << model.nq << ", nv: " << model.nv << std::endl;
  std::cout << data.oMi[(size_t)idx].toHomogeneousMatrix() << std::endl;
  return 0;
}
