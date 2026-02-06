#include <stdio.h>
#include <stdint.h>
extern "C" {
#include <ffmpeg_mediametadataretriever.h>
}

int main() {
    State* s = NULL;
    const char* val = extract_metadata(&s, "duration");
    if (val) {
        printf("duration=%s\n", val);
    } else {
        printf("no duration available (as expected)\n");
    }
    release(&s);
    return 0;
}
