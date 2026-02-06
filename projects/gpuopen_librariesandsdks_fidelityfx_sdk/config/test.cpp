#include <iostream>
#include <ffx_api.hpp>

int main() {
    ffx::ConfigureDescGlobalDebug1 cfg;
    cfg.fpMessage = nullptr;
    cfg.debugLevel = FFX_API_CONFIGURE_GLOBALDEBUG_LEVEL_ERRORS;

    ffx::QueryDescGetVersions qv;
    qv.createDescType = FFX_API_EFFECT_ID_GENERAL;
    qv.device = nullptr;
    uint64_t count = 0;
    qv.outputCount = &count;
    qv.versionIds = nullptr;
    qv.versionNames = nullptr;

    auto* chain = ffx::LinkHeaders(cfg.header, qv.header);
    if (!chain || chain->pNext == nullptr) {
        std::cerr << "LinkHeaders failed" << std::endl;
        return 1;
    }

    ffx::ReturnCode rc = ffx::ReturnCode::Ok;
    if (!rc) {
        // rc is Ok
    }

    std::cout << "FFX API headers are available. Chain type: " << (unsigned long long)chain->type << std::endl;
    return 0;
}
