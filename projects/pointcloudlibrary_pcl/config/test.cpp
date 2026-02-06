#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/centroid.h>
#include <iostream>

int main() {
    pcl::PointCloud<pcl::PointXYZ> cloud;
    cloud.push_back(pcl::PointXYZ(0.0f, 0.0f, 0.0f));
    cloud.push_back(pcl::PointXYZ(1.0f, 0.0f, 0.0f));
    cloud.push_back(pcl::PointXYZ(0.0f, 1.0f, 0.0f));

    Eigen::Vector4f centroid;
    if (pcl::compute3DCentroid(cloud, centroid) >= 0) {
        std::cout << "Centroid: " << centroid.head<3>().transpose() << std::endl;
    } else {
        std::cout << "Failed to compute centroid" << std::endl;
    }
    return 0;
}
