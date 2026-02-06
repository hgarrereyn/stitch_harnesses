ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Dependencies for building
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    make \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build
WORKDIR /fuzz/build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S /fuzz/src -B . -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_WASI=none \
    -DBUILD_NATIVE=OFF
RUN cmake --build . -j"$(nproc)" && cmake --install .

# Install static lib and public headers
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
    && cp -v source/libm3.a /fuzz/install/lib/ \
    && cp -v /fuzz/src/source/wasm3_defs.h /fuzz/src/source/wasm3.h /fuzz/install/include/
