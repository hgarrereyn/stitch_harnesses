#include <stdio.h>
#include <stdlib.h>
#include "bitmask.h"

int main() {
    bitmask_t *a = bitmask_create(64, 64);
    bitmask_t *b = bitmask_create(64, 64);
    if (!a || !b) {
        fprintf(stderr, "Failed to create bitmasks\n");
        return 1;
    }

    // Draw a small square in each mask at different positions
    for (int y = 10; y < 20; ++y) {
        for (int x = 10; x < 20; ++x) {
            bitmask_setbit(a, x, y);
        }
    }
    for (int y = 15; y < 25; ++y) {
        for (int x = 15; x < 25; ++x) {
            bitmask_setbit(b, x, y);
        }
    }

    int overlap = bitmask_overlap(a, b, 0, 0);
    unsigned int count = bitmask_count(a);

    printf("overlap=%d count_a=%u\n", overlap, count);

    bitmask_free(a);
    bitmask_free(b);
    return 0;
}
