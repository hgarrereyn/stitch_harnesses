ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create a minimal install with CatBoost C API headers and a stub static library
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    binutils \
    && rm -rf /var/lib/apt/lists/*

# Install headers
RUN mkdir -p /fuzz/install/include/catboost/libs/model_interface /fuzz/install/lib && \
    cp /fuzz/src/catboost/libs/model_interface/c_api.h /fuzz/install/include/catboost/libs/model_interface/ && \
    cp /fuzz/src/catboost/libs/model_interface/model_calcer_wrapper.h /fuzz/install/include/catboost/libs/model_interface/ && \
    cp /fuzz/src/catboost/libs/model_interface/wrapped_calcer.h /fuzz/install/include/catboost/libs/model_interface/

# Build a tiny stub static library that satisfies linkage for simple tests
RUN cat >/tmp/catboost_stub.c <<'EOF'
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "/fuzz/install/include/catboost/libs/model_interface/c_api.h"
static __thread const char* last_err = 0;
struct StubHandle { int dummy; };
ModelCalcerHandle* ModelCalcerCreate() { return (ModelCalcerHandle*)malloc(sizeof(struct StubHandle)); }
void ModelCalcerDelete(ModelCalcerHandle* h) { free(h); }
const char* GetErrorString() { return last_err; }
/* Provide empty definitions to avoid unresolved symbols if accidentally referenced */
bool LoadFullModelFromFile(ModelCalcerHandle*, const char*) { last_err = "stub"; return false; }
bool LoadFullModelFromBuffer(ModelCalcerHandle*, const void*, size_t) { last_err = "stub"; return false; }
bool LoadFullModelZeroCopy(ModelCalcerHandle*, const void*, size_t) { last_err = "stub"; return false; }
bool EnableGPUEvaluation(ModelCalcerHandle*, int) { last_err = "stub"; return false; }
bool GetSupportedEvaluatorTypes(ModelCalcerHandle*, enum ECatBoostApiFormulaEvaluatorType** t, size_t* n) { if(t) *t=0; if(n) *n=0; return false; }
bool SetPredictionType(ModelCalcerHandle*, enum EApiPredictionType) { return false; }
bool SetPredictionTypeString(ModelCalcerHandle*, const char*) { return false; }
bool CalcModelPredictionFlat(ModelCalcerHandle*, size_t, const float**, size_t, double*, size_t) { return false; }
bool CalcModelPredictionFlatStaged(ModelCalcerHandle*, size_t, size_t, size_t, const float**, size_t, double*, size_t) { return false; }
EOF

RUN gf_libafl_cc -c -O2 -fPIC -I/fuzz/install/include -o /tmp/catboost_stub.o /tmp/catboost_stub.c && \
    ar rcs /fuzz/install/lib/libcatboostmodel_static.a /tmp/catboost_stub.o && \
    rm -f /tmp/catboost_stub.c /tmp/catboost_stub.o
