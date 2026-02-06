ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build flex bison zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, install
WORKDIR /fuzz/src

# Build only static runtimes, disable tests to speed up, skip toolchain (compiler) to keep build small
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
    -DSPICY_ENABLE_TESTS=OFF \
    -DBUILD_TOOLCHAIN=OFF \
 && cmake --build build --target install -j$(nproc)
