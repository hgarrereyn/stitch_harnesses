#include <iostream>
#include <Eigen/Dense>
// Force-include ROS stubs via build flags; just include project header here
#include <lidar_camera_calibration/Find_RT.h>

int main() {
    Eigen::Quaterniond a(0.0, 0.0, 0.0, 1.0);
    Eigen::Quaterniond b(0.0, 1.0, 0.0, 0.0);
    auto c = addQ(a, b);
    std::cout << "Sum quaternion: (" << c.w() << ", " << c.x() << ", " << c.y() << ", " << c.z() << ")\n";
    return 0;
}
