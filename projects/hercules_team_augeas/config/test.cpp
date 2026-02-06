#include <stdio.h>
#include <augeas.h>

int main() {
    // Initialize Augeas with default root and load path, no flags
    augeas *aug = aug_init(NULL, NULL, AUG_NO_LOAD);
    if (!aug) {
        fprintf(stderr, "aug_init failed\n");
        return 1;
    }
    // Define a simple variable and then remove it
    int r = aug_defvar(aug, "root", "/");
    if (r < 0) {
        fprintf(stderr, "aug_defvar failed\n");
        aug_close(aug);
        return 1;
    }
    // Set and get a path in the tree (in-memory since we didn't load files)
    r = aug_set(aug, "/test/node", "value");
    if (r < 0) {
        fprintf(stderr, "aug_set failed\n");
        aug_close(aug);
        return 1;
    }
    const char *val = NULL;
    r = aug_get(aug, "/test/node", &val);
    if (r < 0 || !val) {
        fprintf(stderr, "aug_get failed\n");
        aug_close(aug);
        return 1;
    }
    printf("Got: %s\n", val);
    aug_close(aug);
    return 0;
}
