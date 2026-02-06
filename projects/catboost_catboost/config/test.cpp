#include <catboost/libs/model_interface/c_api.h>
#include <cstdio>

int main() {
    ModelCalcerHandle* h = ModelCalcerCreate();
    if (!h) {
        printf("Failed to create model handle\n");
        return 1;
    }
    ModelCalcerDelete(h);
    const char* err = GetErrorString();
    if (err) {
        printf("GetErrorString: %s\n", err);
    } else {
        printf("No error string available (as expected)\n");
    }
    return 0;
}
