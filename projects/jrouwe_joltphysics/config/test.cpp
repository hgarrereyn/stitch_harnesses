#include <Jolt/Jolt.h>
#include <iostream>

using namespace JPH;

int main() {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);
    float dot = a.Dot(b);
    Vec3 c = a + b;
    std::cout << "Dot: " << dot << ", Sum: (" << c.GetX() << ", " << c.GetY() << ", " << c.GetZ() << ")\n";
    return 0;
}
