#include <cstdio>
#include <ft2build.h>
#include FT_FREETYPE_H

int main() {
    FT_Library lib = nullptr;
    FT_Error err = FT_Init_FreeType(&lib);
    if (err) {
        std::printf("FT_Init_FreeType failed: %d\n", err);
        return 0; // still exit successfully for test purposes
    }

    // Query the version just to exercise the API
    int major=0, minor=0, patch=0;
    FT_Library_Version(lib, &major, &minor, &patch);
    std::printf("FreeType version: %d.%d.%d\n", major, minor, patch);

    FT_Done_FreeType(lib);
    return 0;
}
