#include <math/mathfwd.h>
#include <math/vec3.h>
#include <iostream>

int main() {
    using namespace filament::math;
    float3 a{1.0f, 2.0f, 3.0f};
    float3 b{4.0f, 5.0f, 6.0f};
    float3 c = a + b;
    std::cout << c.x << "," << c.y << "," << c.z << "\n";
    // simple deterministic check
    if (c.x != 5.0f || c.y != 7.0f || c.z != 9.0f) return 1;
    return 0;
}
