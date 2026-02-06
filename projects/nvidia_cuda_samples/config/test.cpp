#include <iostream>
#include <math.h>
#include <nvVector.h>
#include <nvMatrix.h>
#include <nvQuaternion.h>

int main() {
    using namespace nv;
    vec3<float> a(1.0f, 2.0f, 3.0f);
    vec3<float> b(4.0f, 5.0f, 6.0f);

    vec3<float> c = a + b;
    vec3<float> d = a * 2.0f;

    float dot = a.x * b.x + a.y * b.y + a.z * b.z;

    // Construct a quaternion around Y axis by 1 radian
    quaternion<float> q(vec3<float>(0.0f, 1.0f, 0.0f), 1.0f);

    std::cout << "c: (" << c.x << ", " << c.y << ", " << c.z << ")\n";
    std::cout << "d: (" << d.x << ", " << d.y << ", " << d.z << ")\n";
    std::cout << "dot(a,b): " << dot << "\n";
    // Just ensure q is used
    (void)q;
    return 0;
}
