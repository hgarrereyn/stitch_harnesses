ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        libssl-dev \
        libevent-dev \
        pkg-config \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Use fuzzer compilers
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF

# Build and install
RUN cmake --build build --target install
