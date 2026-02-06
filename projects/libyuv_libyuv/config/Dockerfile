ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build libyuv using CMake
WORKDIR /fuzz/src

# Create build directory
RUN mkdir -p build && cd build \
 && cmake -G "Ninja" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    .. \
 && ninja -v \
 && ninja install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
