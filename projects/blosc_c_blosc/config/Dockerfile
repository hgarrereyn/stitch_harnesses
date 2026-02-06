ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates cmake make ninja-build pkg-config build-essential \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install c-blosc as a static library
WORKDIR /fuzz/src

# Configure
RUN cmake -S . -B build \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED=OFF \
    -DBUILD_STATIC=ON \
    -DBUILD_TESTS=OFF \
    -DBUILD_FUZZERS=OFF \
    -DBUILD_BENCHMARKS=OFF

# Build and install
RUN cmake --build build -j"$(nproc)" && cmake --install build
