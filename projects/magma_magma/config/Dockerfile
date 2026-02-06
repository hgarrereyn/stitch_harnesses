ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal build tools needed for this target
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Build only the small LTE_GATEWAY_C_COMMON static library and install headers
ENV MAGMA_ROOT=/fuzz/src

# Configure and build the library with fuzzing compilers
RUN cmake -G Ninja \
    -S /fuzz/src/lte/gateway/c/core/common \
    -B /tmp/build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
  && cmake --build /tmp/build -j

# Manually install static lib and public headers
RUN mkdir -p /fuzz/install/lib \
    && cp /tmp/build/libLTE_GATEWAY_C_COMMON.a /fuzz/install/lib/ \
    && mkdir -p /fuzz/install/include/lte/gateway/c/core/common \
    && cp /fuzz/src/lte/gateway/c/core/common/assertions.h /fuzz/install/include/lte/gateway/c/core/common/ \
    && cp /fuzz/src/lte/gateway/c/core/common/backtrace.h /fuzz/install/include/lte/gateway/c/core/common/ \
    && cp /fuzz/src/lte/gateway/c/core/common/common_defs.h /fuzz/install/include/lte/gateway/c/core/common/ \
    && cp /fuzz/src/lte/gateway/c/core/common/dynamic_memory_check.h /fuzz/install/include/lte/gateway/c/core/common/ \
    && mkdir -p /fuzz/install/include/lte/gateway/c/core/oai/lib/bstr \
    && cp /fuzz/src/lte/gateway/c/core/oai/lib/bstr/bstrlib.h /fuzz/install/include/lte/gateway/c/core/oai/lib/bstr/
