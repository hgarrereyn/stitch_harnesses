#include <iostream>
#include <vector>
#include <LightGBM/c_api.h>

int main() {
    float data[8] = {1.0f,2.0f, 1.5f,1.8f, 3.0f,3.2f, 2.5f,2.7f};
    float labels[4] = {0.0f, 0.0f, 1.0f, 1.0f};

    DatasetHandle dtrain = nullptr;
    int ret = LGBM_DatasetCreateFromMat(
        data,
        C_API_DTYPE_FLOAT32,
        4,
        2,
        1,
        "max_bin=15",
        nullptr,
        &dtrain);
    if (ret != 0) { std::cerr << "CreateFromMat failed: " << LGBM_GetLastError() << std::endl; return 1; }

    ret = LGBM_DatasetSetField(dtrain, "label", labels, 4, C_API_DTYPE_FLOAT32);
    if (ret != 0) { std::cerr << "SetField(label) failed: " << LGBM_GetLastError() << std::endl; return 1; }

    BoosterHandle booster = nullptr;
    ret = LGBM_BoosterCreate(dtrain, "objective=binary num_leaves=3 min_data_in_leaf=1 bagging_fraction=1 feature_fraction=1 num_threads=1", &booster);
    if (ret != 0) { std::cerr << "BoosterCreate failed: " << LGBM_GetLastError() << std::endl; return 1; }

    int empty = 0;
    for (int i = 0; i < 3; ++i) {
        ret = LGBM_BoosterUpdateOneIter(booster, &empty);
        if (ret != 0) { std::cerr << "UpdateOneIter failed: " << LGBM_GetLastError() << std::endl; return 1; }
    }

    int64_t out_len = 0;
    ret = LGBM_BoosterGetNumPredict(booster, 0, &out_len);
    if (ret != 0) { std::cerr << "GetNumPredict failed: " << LGBM_GetLastError() << std::endl; return 1; }

    std::vector<double> preds(out_len);
    ret = LGBM_BoosterGetPredict(booster, 0, &out_len, preds.data());
    if (ret != 0) { std::cerr << "GetPredict failed: " << LGBM_GetLastError() << std::endl; return 1; }

    std::cout << "Predictions (" << out_len << "):";
    for (int64_t i = 0; i < out_len; ++i) std::cout << ' ' << preds[i];
    std::cout << std::endl;

    LGBM_BoosterFree(booster);
    LGBM_DatasetFree(dtrain);
    return 0;
}
