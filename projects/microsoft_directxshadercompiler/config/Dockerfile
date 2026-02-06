ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    make \
    python3 \
    ninja-build \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure and prepare headers install
WORKDIR /fuzz

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -C /fuzz/src/cmake/caches/PredefinedParams.cmake \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Install only the public headers to keep image small and builds fast
RUN cmake --build /fuzz/build --target install-dxc-headers
