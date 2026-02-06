#include <cstdio>
#define FUSE_USE_VERSION 31
#include "/fuzz/install/include/fuse3/fuse.h"

int main() {
    int v = fuse_version();
    printf("libfuse version (FUSE_USE_VERSION=%d): %d\n", FUSE_USE_VERSION, v);
    const char *argvv[] = {"prog"};
    int argc = 1;
    struct fuse_args args = FUSE_ARGS_INIT(argc, (char **)argvv);
    fuse_opt_free_args(&args);
    return 0;
}
