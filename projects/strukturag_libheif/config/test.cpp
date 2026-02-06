#include <cstdio>
#include <cstdint>
#include <libheif/heif.h>

int main() {
    // Print the libheif version obtained from the library
    const char* ver = heif_get_version();
    uint32_t ver_num = heif_get_version_number();
    std::printf("libheif version: %s (0x%08x)\n", ver ? ver : "(null)", ver_num);

    // Simple init/deinit cycle
    heif_init_params params{}; // defaults
    heif_error err = heif_init(&params);
    if (err.code != heif_error_Ok) {
        std::printf("heif_init failed: %d\n", (int)err.code);
    }

    heif_deinit();
    return 0;
}
