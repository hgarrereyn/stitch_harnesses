#include <iostream>
#include <SPlisHSPlasH/SPHKernels.h>

int main() {
    using namespace SPH;
    CubicKernel::setRadius(1.0f);
    Vector3r r(0.25f, 0.0f, 0.0f);
    Real w_val = CubicKernel::W(r);
    std::cout << "CubicKernel W(0.25) = " << static_cast<double>(w_val) << std::endl;
    return 0;
}
