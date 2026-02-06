ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install brotli as static libs
WORKDIR /fuzz/src

RUN mkdir -p build && cd build \
 && cmake -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DBROTLI_BUILD_TOOLS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    .. \
 && ninja -v \
 && ninja install
