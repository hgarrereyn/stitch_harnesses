#include <iostream>
extern "C" {
#include <liblwgeom/liblwgeom.h>
}

int main() {
    const char* ver = lwgeom_version();
    std::cout << "liblwgeom version: " << (ver ? ver : "(null)") << "\n";
    POINT2D p{1.23, 4.56};
    std::cout << "Point: (" << p.x << ", " << p.y << ")\n";
    return 0;
}
