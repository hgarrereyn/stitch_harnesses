#include <ass/ass.h>
#include <cstdio>

int main() {
    // Print version and init/done library to ensure basic API works
    int ver = ass_library_version();
    std::printf("libass version: 0x%08x\n", ver);

    ASS_Library *lib = ass_library_init();
    if (!lib) {
        std::printf("Failed to init libass\n");
        return 1;
    }
    ass_library_done(lib);
    return 0;
}
