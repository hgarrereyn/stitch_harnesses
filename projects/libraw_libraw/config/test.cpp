#include <iostream>
#include <libraw/libraw.h>
#include <libraw/libraw_version.h>

int main() {
    std::cout << "LibRaw version (compile-time): " << LIBRAW_VERSION_STR << "\n";
    // Use C API
    libraw_data_t* proc = libraw_init(0);
    if (!proc) {
        std::cout << "libraw_init failed\n";
        return 1;
    }
    std::cout << "libraw_strerror(0): " << libraw_strerror(0) << "\n";
    libraw_close(proc);

    // Minimal class usage to ensure C++ symbols are linked
    LibRaw lr;
    // We won't open a file; just query some fields
    std::cout << "Imgdata idata is_foveon: " << lr.imgdata.idata.is_foveon << "\n";

    return 0;
}
