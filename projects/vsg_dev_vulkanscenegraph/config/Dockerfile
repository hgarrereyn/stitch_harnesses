ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: CMake/Ninja, Vulkan headers/loader, pkg-config, xcb for windowing
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libvulkan-dev \
    libxcb1-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with CMake using the required compilers and static libs where possible
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF

RUN cmake --build build -j
RUN cmake --install build
