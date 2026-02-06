ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static library from the Common SVariant C module (no Qt deps)
RUN apt-get update && apt-get install -y --no-install-recommends make ca-certificates pkg-config && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Patch Windows-style includes and build/install static lib and headers
RUN mkdir -p /fuzz/build /fuzz/install/include/TaskExplorer/Common /fuzz/install/lib && \
    cp /fuzz/src/TaskExplorer/Common/SVariant.c /fuzz/build/ && \
    cp /fuzz/src/TaskExplorer/Common/SVariant.h /fuzz/build/ && \
    cp /fuzz/src/TaskExplorer/Common/Types.h /fuzz/build/ && \
    cp /fuzz/src/TaskExplorer/Common/VariantDefs.h /fuzz/build/ && \
    sed -i 's#"..\\Types.h"#"Types.h"#' /fuzz/build/SVariant.h && \
    cd /fuzz/build && \
    gf_libafl_cc -O2 -fPIC -include string.h -include limits.h -I/fuzz/build -c SVariant.c -o SVariant.o && \
    ar rcs libtaskexplorer.a SVariant.o && \
    cp libtaskexplorer.a /fuzz/install/lib/ && \
    mkdir -p /fuzz/install/include/TaskExplorer/Common && \
    cp /fuzz/build/SVariant.h /fuzz/install/include/TaskExplorer/Common/ && \
    cp /fuzz/build/VariantDefs.h /fuzz/install/include/TaskExplorer/Common/ && \
    cp /fuzz/build/Types.h /fuzz/install/include/TaskExplorer/Common/
