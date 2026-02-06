#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ten_vad.h"

int main() {
    ten_vad_handle_t handle = NULL;
    size_t hop = 256;
    float threshold = 0.5f;
    if (ten_vad_create(&handle, hop, threshold) != 0 || handle == NULL) {
        fprintf(stderr, "ten_vad_create failed\n");
        return 1;
    }

    int16_t *buf = (int16_t*)calloc(hop, sizeof(int16_t));
    if (!buf) {
        fprintf(stderr, "alloc failed\n");
        return 1;
    }

    float prob = -1.0f;
    int flag = -1;
    if (ten_vad_process(handle, buf, hop, &prob, &flag) != 0) {
        fprintf(stderr, "ten_vad_process failed\n");
        free(buf);
        ten_vad_destroy(&handle);
        return 1;
    }

    printf("Version: %s\n", ten_vad_get_version());
    printf("Prob=%.6f Flag=%d\n", prob, flag);

    free(buf);
    if (ten_vad_destroy(&handle) != 0) {
        fprintf(stderr, "ten_vad_destroy failed\n");
        return 1;
    }
    return 0;
}
