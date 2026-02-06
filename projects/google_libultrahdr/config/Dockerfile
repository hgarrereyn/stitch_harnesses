ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libjpeg-turbo8-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install libultrahdr
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DUHDR_BUILD_EXAMPLES=OFF \
    -DUHDR_BUILD_TESTS=OFF \
    -DUHDR_BUILD_BENCHMARK=OFF \
    -DUHDR_BUILD_FUZZERS=OFF \
    -DUHDR_BUILD_DEPS=OFF \
    -G Ninja && \
    cmake --build build --config Release && \
    cmake --install build --config Release
