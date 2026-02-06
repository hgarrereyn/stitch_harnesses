ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (ensure cmake/ninja are present) and minimal deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src/build

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Configure: build only static lib, no tools/plugins/tests/llvm
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWASMEDGE_BUILD_STATIC_LIB=ON \
    -DWASMEDGE_BUILD_SHARED_LIB=OFF \
    -DWASMEDGE_BUILD_TOOLS=OFF \
    -DWASMEDGE_BUILD_PLUGINS=OFF \
    -DWASMEDGE_USE_LLVM=OFF \
    -DWASMEDGE_BUILD_TESTS=OFF \
    -DWASMEDGE_BUILD_EXAMPLE=OFF \
    -DWASMEDGE_BUILD_WASI_NN_RPC=OFF \
    ..

RUN ninja -j"$(nproc)" install
