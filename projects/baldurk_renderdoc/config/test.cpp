#include <iostream>
#include <stdint.h>
#include <renderdoc_app.h>

int main() {
    uint8_t magic[16] = RENDERDOC_ShaderDebugMagicValue_bytearray;
    unsigned long long acc = 0;
    for (int i = 0; i < 16; ++i) acc += magic[i];
    RENDERDOC_CaptureOption opt = eRENDERDOC_Option_AllowVSync;
    (void)opt;
    std::cout << "RenderDoc header OK, magic checksum=" << acc << "\n";
    return 0;
}
