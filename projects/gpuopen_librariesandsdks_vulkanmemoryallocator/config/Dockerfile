ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and Vulkan headers/loader
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake \
        libvulkan-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and install the header-only library
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DVMA_ENABLE_INSTALL=ON \
    -DVMA_BUILD_SAMPLES=OFF

RUN cmake --build build -j$(nproc) && \
    cmake --install build --prefix /fuzz/install
