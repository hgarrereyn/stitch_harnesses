ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build/runtime deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    git \
    cmake \
    ninja-build \
    pkg-config \
    libcurl4-openssl-dev \
    libffi-dev \
 && rm -rf /var/lib/apt/lists/*

# Fetch submodules
WORKDIR /fuzz/src
RUN git submodule update --init --recursive

# Configure and build (static library only)
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_WITH_MIMALLOC=OFF \
    -DUSE_EXTERNAL_FFI=ON
RUN cmake --build /fuzz/build --target tjs tjs-cli -j$(nproc)

# "Install" artifacts we need for consumers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp /fuzz/build/libtjs.a /fuzz/install/lib/ \
 && cp /fuzz/src/src/tjs.h /fuzz/install/include/ \
 && cp /fuzz/src/deps/quickjs/quickjs.h /fuzz/install/include/
