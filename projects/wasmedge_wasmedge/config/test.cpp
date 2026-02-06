#include <wasmedge/wasmedge.h>
#include <cstdio>
#include <cstdint>

int main() {
    const char* ver = WasmEdge_VersionGet();
    uint32_t maj = WasmEdge_VersionGetMajor();
    uint32_t min = WasmEdge_VersionGetMinor();
    uint32_t pat = WasmEdge_VersionGetPatch();

    WasmEdge_LogSetErrorLevel();

    std::printf("WasmEdge CAPI version: %s (%u.%u.%u)\n", ver ? ver : "(null)", maj, min, pat);

    WasmEdge_ConfigureContext* Conf = WasmEdge_ConfigureCreate();
    if (Conf) {
        WasmEdge_ConfigureDelete(Conf);
    }

    return 0;
}
