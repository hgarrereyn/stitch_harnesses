ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    curl \
    pkg-config \
    python3 \
    python3-pip \
    ninja-build \
    make \
    autoconf \
    automake \
    libtool \
    unzip \
    tar \
    && rm -rf /var/lib/apt/lists/*

# Newer CMake than Ubuntu 22.04 provides
RUN pip3 install --no-cache-dir cmake==3.28.4

# Build Arrow C++ with minimal features and bundled third-party deps
WORKDIR /fuzz/src/cpp

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S . -B build \
    -GNinja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DARROW_BUILD_SHARED=ON \
    -DARROW_BUILD_STATIC=OFF \
    -DARROW_DEPENDENCY_SOURCE=BUNDLED \
    -DARROW_COMPUTE=OFF \
    -DARROW_CSV=OFF \
    -DARROW_JSON=OFF \
    -DARROW_IPC=OFF \
    -DARROW_FILESYSTEM=OFF \
    -DARROW_PARQUET=OFF \
    -DARROW_WITH_RE2=OFF \
    -DARROW_WITH_ZLIB=OFF \
    -DARROW_WITH_LZ4=OFF \
    -DARROW_WITH_ZSTD=OFF \
    -DARROW_WITH_SNAPPY=OFF \
    -DARROW_GANDIVA=OFF \
    -DARROW_DATASET=OFF \
    -DARROW_FLIGHT=OFF \
    -DARROW_TESTING=OFF \
    && cmake --build build --target arrow_shared \
    && cmake --install build

# Ensure the shared library is discoverable at runtime
ENV LD_LIBRARY_PATH=/fuzz/install/lib:${LD_LIBRARY_PATH}
