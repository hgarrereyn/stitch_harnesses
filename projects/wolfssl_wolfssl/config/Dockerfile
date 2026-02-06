ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and any extra dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates build-essential cmake ninja-build pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Use fuzzing compiler wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure with CMake: static library only, install to /fuzz/install
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DWOLFSSL_INSTALL=ON

# Build and install
RUN cmake --build build --parallel && cmake --install build
