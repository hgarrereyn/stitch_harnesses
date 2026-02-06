#include <cstdio>
#include <graalnode/node_version.h>

int main() {
    // Print Node.js version macros from the header we installed
    printf("Node version: %s\n", NODE_VERSION);
    printf("Major: %d Minor: %d Patch: %d\n", NODE_MAJOR_VERSION, NODE_MINOR_VERSION, NODE_PATCH_VERSION);
    return 0;
}
