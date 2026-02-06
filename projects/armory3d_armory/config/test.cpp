#include <bullet/btBulletDynamicsCommon.h>
#include <iostream>

int main() {
    // Use a simple header-only type from LinearMath to avoid needing libraries
    btVector3 a(1.0f, 2.0f, 3.0f);
    btVector3 b(4.0f, -1.0f, 0.5f);
    btVector3 c = a + b;
    std::cout << "Length: " << c.length() << "\n";
    // Ensure some basic operations are exercised
    c.normalize();
    std::cout << "Normalized Z: " << c.getZ() << "\n";
    return 0;
}
