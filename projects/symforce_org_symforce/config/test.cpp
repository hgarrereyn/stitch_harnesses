#include <iostream>
#include <sym/pose2.h>

int main() {
    // Construct and use a generated SymForce type to verify headers and linking
    sym::Pose2<double> p = sym::Pose2<double>::Identity();
    auto t = p.Position();
    std::cout << "Pose2 Identity translation: [" << t(0) << ", " << t(1) << "]\n";
    return 0;
}
