#include <mpg123.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    if (mpg123_init() != MPG123_OK) {
        std::fprintf(stderr, "mpg123_init failed\n");
        return 1;
    }

    int err = MPG123_OK;
    mpg123_handle* mh = mpg123_new(NULL, &err);
    if (!mh) {
        std::fprintf(stderr, "mpg123_new failed: %s\n", mpg123_plain_strerror(err));
        mpg123_exit();
        return 1;
    }

    // Use feed API with some dummy bytes (not a valid MP3). We just drive a few API calls.
    if (mpg123_open_feed(mh) != MPG123_OK) {
        std::fprintf(stderr, "mpg123_open_feed failed\n");
    }

    const unsigned char dummy[16] = {0};
    size_t done = 0;
    mpg123_feed(mh, dummy, sizeof(dummy));

    long rate = 0; int channels = 0; int enc = 0;
    (void)mpg123_getformat(mh, &rate, &channels, &enc);

    // Clean up
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    std::puts("mpg123 minimal test OK");
    return 0;
}
