#include <iostream>
#include <pointmatcher/PointMatcher.h>

int main() {
    typedef PointMatcher<float> PM;

    // Create two tiny identical point clouds (3D with homogeneous coord)
    PM::DataPoints::Labels featLabels; 
    featLabels.push_back(PM::DataPoints::Label("x",1));
    featLabels.push_back(PM::DataPoints::Label("y",1));
    featLabels.push_back(PM::DataPoints::Label("z",1));
    featLabels.push_back(PM::DataPoints::Label("w",1)); // homogeneous coordinate

    PM::DataPoints reading(featLabels, PM::DataPoints::Labels(), 3);
    PM::DataPoints reference(featLabels, PM::DataPoints::Labels(), 3);

    // Fill a simple triangle in both clouds
    reading.features.setZero();
    reference.features.setZero();

    // points
    reading.features(0,0) = 0.f; reading.features(1,0) = 0.f; reading.features(2,0) = 0.f; reading.features(3,0) = 1.f;
    reading.features(0,1) = 1.f; reading.features(1,1) = 0.f; reading.features(2,1) = 0.f; reading.features(3,1) = 1.f;
    reading.features(0,2) = 0.f; reading.features(1,2) = 1.f; reading.features(2,2) = 0.f; reading.features(3,2) = 1.f;

    reference.features = reading.features; // identical clouds

    // Build a default ICP pipeline and run alignment
    PM::ICP icp;
    icp.setDefault();

    PM::TransformationParameters T = icp(reading, reference);

    std::cout << "Estimated transformation (should be identity):\n" << T << std::endl;

    // Simple sanity check: identity expected
    if ((T - PM::TransformationParameters::Identity(4,4)).array().abs().maxCoeff() < 1e-3) {
        std::cout << "OK" << std::endl;
        return 0;
    }
    std::cout << "Unexpected transform" << std::endl;
    return 0;
}
