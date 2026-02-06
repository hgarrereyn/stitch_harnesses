#include <iostream>
#include <Horde3D.h>
#include <Horde3DUtils.h>

int main() {
    const char* ver = h3dGetVersionString();
    if (!ver) ver = "unknown";
    std::cout << "Horde3D version: " << ver << "\n";
    // Do not initialize the engine (requires an OpenGL context). Just touch a utils symbol too.
    const char* path = h3dutGetResourcePath(0);
    std::cout << "Default resource path: " << (path ? path : "(null)") << "\n";
    return 0;
}
