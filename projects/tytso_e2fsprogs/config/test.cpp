#include <cstdio>
#include <ext2fs/ext2fs.h>

int main() {
    const char *ver = nullptr; const char *date = nullptr;
    int major = ext2fs_get_library_version(&ver, &date);
    if (!ver || !date) return 1;
    std::printf("libext2fs version: %s (parsed major: %d) built on %s\n", ver, major, date);
    return 0;
}
