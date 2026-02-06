#include <cstdio>
#include <cstring>
extern "C" {
#include <magic.h>
}

int main() {
    // Open magic cookie with MIME type flag (exercise a common code path)
    magic_t m = magic_open(MAGIC_MIME);
    if (!m) {
        std::printf("magic_open failed\n");
        return 1;
    }
    // Load default magic database installed by the build
    if (magic_load(m, nullptr) != 0) {
        std::printf("magic_load failed: %s\n", magic_error(m));
        magic_close(m);
        return 1;
    }
    const char data[] = "Hello, world!\n";
    const char* desc = magic_buffer(m, data, sizeof(data));
    if (!desc) {
        std::printf("magic_buffer failed: %s\n", magic_error(m));
        magic_close(m);
        return 1;
    }
    std::printf("Description: %s\n", desc);
    magic_close(m);
    return 0;
}
