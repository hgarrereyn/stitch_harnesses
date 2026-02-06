#include <cstdio>
#include <spirv-tools/libspirv.h>

int main() {
    const char* ver = spvSoftwareVersionString();
    if (!ver) return 1;
    printf("SPIRV-Tools version: %s\n", ver);
    // Create and destroy a context to exercise basic API
    spv_target_env env = SPV_ENV_UNIVERSAL_1_3;
    spv_context ctx = spvContextCreate(env);
    if (!ctx) return 2;
    spvContextDestroy(ctx);
    return 0;
}
