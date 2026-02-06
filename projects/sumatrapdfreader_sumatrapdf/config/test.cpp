#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <unarr.h>
}

int main() {
    const unsigned char data[] = {0x00, 0x00, 0x00, 0x00};
    ar_stream* s = ar_open_memory(data, sizeof(data));
    if (!s) {
        printf("ar_open_memory failed\n");
        return 0;
    }
    // Try opening as different archive types; these should fail on random data
    ar_archive* azip = ar_open_zip_archive(s, true);
    if (azip) {
        // unlikely, but clean up
        ar_close_archive(azip);
    }
    ar_archive* arar = ar_open_rar_archive(s);
    if (arar) {
        ar_close_archive(arar);
    }
    ar_archive* atar = ar_open_tar_archive(s);
    if (atar) {
        ar_close_archive(atar);
    }
    ar_archive* a7z = ar_open_7z_archive(s);
    if (a7z) {
        ar_close_archive(a7z);
    }
    ar_close(s);
    printf("unarr basic test completed\n");
    return 0;
}
