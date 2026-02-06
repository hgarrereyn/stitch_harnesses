#include <cstdio>
#include <cstring>
#include <libcue.h>

int main() {
    const char *cue_text =
        "CATALOG 0123456789012\n"
        "FILE \"test.wav\" WAVE\n"
        "  TRACK 01 AUDIO\n"
        "    TITLE \"Song One\"\n"
        "    PERFORMER \"Artist\"\n"
        "    INDEX 01 00:00:00\n";

    Cd *cd = cue_parse_string(cue_text);
    if (!cd) {
        printf("Failed to parse cue string\n");
        return 1;
    }

    int n = cd_get_ntrack(cd);
    printf("Parsed tracks: %d\n", n);

    const char *catalog = cd_get_catalog(cd);
    if (catalog) {
        printf("Catalog: %s\n", catalog);
    }

    Track *t = cd_get_track(cd, 1);
    if (t) {
        const char *fname = track_get_filename(t);
        long start = track_get_start(t);
        printf("Track1 file: %s start: %ld\n", fname ? fname : "(null)", start);
    }

    cd_delete(cd);
    return 0;
}
