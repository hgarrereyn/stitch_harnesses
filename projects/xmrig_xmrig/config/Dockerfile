ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libuv1-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure and build xmrig executable with minimal dependencies
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWITH_TLS=OFF \
    -DWITH_HTTP=OFF \
    -DWITH_HWLOC=OFF \
    -DWITH_OPENCL=OFF \
    -DWITH_CUDA=OFF \
    -DWITH_NVML=OFF \
    -DWITH_ADL=OFF \
    -DWITH_BENCHMARK=OFF \
 && cmake --build build -j$(nproc)

# "Install" headers for downstream consumers and create lib dir placeholder
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /fuzz/install/bin \
 && cp -r src/* /fuzz/install/include/ \
 && cp build/xmrig /fuzz/install/bin/ || true
