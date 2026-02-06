#include <xgboost/c_api.h>
#include <cstdio>

int main() {
    int major = 0, minor = 0, patch = 0;
    XGBoostVersion(&major, &minor, &patch);
    std::printf("XGBoost v%d.%d.%d\n", major, minor, patch);

    BoosterHandle booster = nullptr;
    int rc = XGBoosterCreate(nullptr, 0, &booster);
    if (rc != 0 || booster == nullptr) {
        std::printf("Failed to create booster: %s\n", XGBGetLastError());
        return 1;
    }

    const char* build_info = nullptr;
    rc = XGBuildInfo(&build_info);
    if (rc == 0 && build_info) {
        std::printf("Build info (prefix): %.60s\n", build_info);
    }

    XGBoosterFree(booster);
    return 0;
}
