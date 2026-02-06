#include <cstdio>
#include <openslide/openslide.h>

int main() {
    const char* ver = openslide_get_version();
    if (!ver) {
        printf("OpenSlide version not found\n");
        return 1;
    }
    printf("OpenSlide version: %s\n", ver);

    // Basic API smoke test: create a cache and immediately release it
    openslide_cache_t* cache = openslide_cache_create(1024 * 1024);
    openslide_cache_release(cache);

    // Detect vendor on a non-existent file should return NULL
    const char* v = openslide_detect_vendor("/nonexistent/file");
    printf("Detect vendor on missing file: %s\n", v ? v : "(none)");

    return 0;
}
