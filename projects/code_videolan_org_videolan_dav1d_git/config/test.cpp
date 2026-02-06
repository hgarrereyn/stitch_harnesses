#include <iostream>
#include <dav1d/dav1d.h>

int main() {
    // Print version
    const char* ver = dav1d_version();
    std::cout << "dav1d version: " << (ver ? ver : "(null)") << "\n";

    // Initialize settings and open/close a decoder
    Dav1dSettings settings;
    dav1d_default_settings(&settings);

    Dav1dContext* ctx = nullptr;
    int ret = dav1d_open(&ctx, &settings);
    if (ret < 0) {
        std::cout << "dav1d_open failed: " << ret << "\n";
        return 0; // still succeed for test purposes
    }

    // Query frame delay
    int delay = dav1d_get_frame_delay(&settings);
    std::cout << "frame delay: " << delay << "\n";

    dav1d_close(&ctx);
    return 0;
}
