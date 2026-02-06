ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building AdaptiveCpp minimal runtime (cmake, ninja, OpenMP, NUMA optional)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libomp-17-dev \
    libnuma-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build and install AdaptiveCpp with minimal features (no LLVM/Clang plugin, only CPU backend)
WORKDIR /fuzz/src

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DACPP_COMPILER_FEATURE_PROFILE=none \
    -DWITH_CUDA_BACKEND=OFF \
    -DWITH_ROCM_BACKEND=OFF \
    -DWITH_OPENCL_BACKEND=OFF \
    -DWITH_LEVEL_ZERO_BACKEND=OFF \
    -G Ninja && \
    cmake --build build --target install -j$(nproc)
