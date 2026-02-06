#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <tectonic_bridge_core.h>
}

int main() {
    // Use a couple of inline helpers/macros from the public header.
    const char *prefix = "Hello";
    const char *s = "Hello, Tectonic";
    const char *rest = strstartswith(s, prefix); // inline helper
    if (rest == nullptr) {
        std::printf("Prefix not found!\n");
        return 1;
    }

    // Use the inline mfree() wrapper from the header.
    char *buf = (char*) std::malloc(32);
    std::snprintf(buf, 32, "%s", rest);
    buf = (char*) mfree(buf);

    // Test a macro from the header
    bool sep = IS_DIR_SEP('/');
    std::printf("All good: rest='%s' sep=%d\n", rest, (int)sep);
    return 0;
}
