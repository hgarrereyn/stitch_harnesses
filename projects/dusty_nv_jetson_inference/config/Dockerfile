ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create and install a minimal stub of the jetson-inference library so linking succeeds
RUN set -eux; \
    mkdir -p /fuzz/install/include/jetson-inference /fuzz/install/lib /tmp/build; \
    printf '%s\n' \
'#ifndef JETSON_INFERENCE_STUB_H' \
'#define JETSON_INFERENCE_STUB_H' \
'namespace jetson_inference_stub {' \
'inline int version() { return 1; }' \
'}' \
'#endif' \
    > /tmp/build/stub.h; \
    printf '%s\n' \
'#include "jetson-inference/stub.h"' \
'namespace jetson_inference_stub { int version(); }' \
'int force_ref() { return jetson_inference_stub::version(); }' \
    > /tmp/build/stub.cpp; \
    cp /tmp/build/stub.h /fuzz/install/include/jetson-inference/stub.h; \
    stitch_libafl_cxx -fPIC -c /tmp/build/stub.cpp -I/fuzz/install/include -o /tmp/build/stub.o; \
    ar rcs /fuzz/install/lib/libjetson-inference.a /tmp/build/stub.o; \
    rm -rf /tmp/build

ENV CPATH=/fuzz/install/include:$CPATH \
    LIBRARY_PATH=/fuzz/install/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/fuzz/install/lib:$LD_LIBRARY_PATH
