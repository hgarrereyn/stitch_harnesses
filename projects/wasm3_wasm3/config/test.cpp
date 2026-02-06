extern "C" {
#include "wasm3.h"
}
#include <iostream>

int main() {
    IM3Environment env = m3_NewEnvironment();
    if (!env) {
        std::cout << "Failed to create environment\n";
        return 0;
    }
    IM3Runtime rt = m3_NewRuntime(env, 64 * 1024, nullptr);
    if (!rt) {
        std::cout << "Failed to create runtime\n";
        m3_FreeEnvironment(env);
        return 0;
    }

    std::cout << "Wasm3 runtime created successfully.\n";

    m3_FreeRuntime(rt);
    m3_FreeEnvironment(env);
    return 0;
}
