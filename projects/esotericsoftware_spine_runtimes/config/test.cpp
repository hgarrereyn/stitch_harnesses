#include <spine/Version.h>
#include <spine/Color.h>
#include <spine/Extension.h>
#include <iostream>

namespace spine {
// Provide default extension implementation required by the library.
SpineExtension* getDefaultExtension() {
    static DefaultSpineExtension ext;
    return &ext;
}
}

int main() {
    spine::Color c(1.2f, -0.5f, 0.5f, 2.0f);
    c.clamp();
    std::cout << "Spine version: " << SPINE_VERSION_STRING << "\n";
    std::cout << "Color: (" << c.r << "," << c.g << "," << c.b << "," << c.a << ")\n";
    return 0;
}
