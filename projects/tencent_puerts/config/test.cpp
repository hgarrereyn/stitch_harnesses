#include <stdio.h>
#include <wasm3/wasm3.h>

int main() {
    IM3Environment env = m3_NewEnvironment();
    if (!env) {
        printf("Failed to create environment\n");
        return 1;
    }
    IM3Runtime rt = m3_NewRuntime(env, 64*1024, NULL);
    if (!rt) {
        printf("Failed to create runtime\n");
        m3_FreeEnvironment(env);
        return 1;
    }

    // Query version and do a trivial API call
    const M3Result ok = m3Err_none;
    if (ok != m3Err_none) {
        printf("Unexpected error constant mismatch\n");
    }

    m3_FreeRuntime(rt);
    m3_FreeEnvironment(env);
    printf("wasm3 basic init/free OK\n");
    return 0;
}
