ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: cmake/ninja, oneTBB and tools to fetch/extract ISPC
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates wget xz-utils \
    cmake ninja-build make pkg-config \
    libtbb-dev && \
    rm -rf /var/lib/apt/lists/*

# Install ISPC (we will bypass version detection by specifying it in CMake cache)
ENV ISPC_VERSION=v1.29.1
RUN wget -O /tmp/ispc.tar.gz https://github.com/ispc/ispc/releases/download/${ISPC_VERSION}/ispc-${ISPC_VERSION}-linux.tar.gz && \
    mkdir -p /opt/ispc && \
    tar -xzf /tmp/ispc.tar.gz -C /opt/ispc --strip-components=1 && \
    ln -sf /opt/ispc/bin/ispc /usr/local/bin/ispc && \
    rm -f /tmp/ispc.tar.gz

# Configure, build, install (CPU-only, no built-in weights to avoid Git LFS)
WORKDIR /fuzz/src
RUN mkdir -p build && cd build && \
    cmake -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DOIDN_STATIC_LIB=ON \
      -DOIDN_APPS=OFF \
      -DOIDN_DEVICE_SYCL=OFF \
      -DOIDN_DEVICE_CUDA=OFF \
      -DOIDN_DEVICE_HIP=OFF \
      -DOIDN_FILTER_RT=OFF \
      -DOIDN_FILTER_RTLIGHTMAP=OFF \
      -DISPC_EXECUTABLE=/opt/ispc/bin/ispc \
      -DISPC_VERSION=1.29.1 \
      .. && \
    ninja -j$(nproc) && \
    ninja install
