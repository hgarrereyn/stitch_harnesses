#include <stdio.h>
#include <stdbool.h>
#include <wasm_export.h>

int main() {
    if (!wasm_runtime_init()) {
        fprintf(stderr, "Failed to init WAMR runtime\n");
        return 1;
    }

    wasm_runtime_set_log_level(WASM_LOG_LEVEL_ERROR);

    bool has_interp = wasm_runtime_is_running_mode_supported(Mode_Interp);
    bool has_any_jit = wasm_runtime_is_running_mode_supported(Mode_Fast_JIT) ||
                       wasm_runtime_is_running_mode_supported(Mode_LLVM_JIT) ||
                       wasm_runtime_is_running_mode_supported(Mode_Multi_Tier_JIT);

    printf("WAMR initialized. interp=%s, any_jit=%s\n",
           has_interp ? "yes" : "no",
           has_any_jit ? "yes" : "no");

    wasm_runtime_destroy();
    return 0;
}
