#include <cstdio>
#include <bgfx/bgfx.h>

int main() {
    // Use existing handle type and inline isValid from the public API.
    bgfx::TextureHandle h = BGFX_INVALID_HANDLE; // idx == kInvalidHandle
    bool valid = bgfx::isValid(h);

    // Also exercise an enum constant from the API to ensure headers parse.
    bgfx::RendererType::Enum r = bgfx::RendererType::Noop;

    std::printf("valid=%d renderer=%d\n", valid ? 1 : 0, (int)r);
    return 0;
}
