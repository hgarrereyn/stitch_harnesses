ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools. Get a modern CMake via pip to satisfy project requirements (>=3.24)
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3-pip \
    ninja-build \
    pkg-config \
    make \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/* && \
    pip3 install --no-cache-dir cmake

WORKDIR /fuzz/src

# Configure and build Blend2D as a static library without JIT to avoid external deps
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBLEND2D_STATIC=ON \
    -DBLEND2D_NO_JIT=ON \
    -DBLEND2D_TEST=OFF \
    -DBLEND2D_DEMOS=OFF \
    -DBLEND2D_NO_INSTALL=OFF \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx

RUN cmake --build /fuzz/build --config Release && \
    cmake --install /fuzz/build
