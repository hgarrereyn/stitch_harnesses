ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building RocksDB with common compression libraries
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
    libsnappy-dev \
    zlib1g-dev \
    libbz2-dev \
    liblz4-dev \
    libzstd-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install RocksDB (static library preferred)
WORKDIR /fuzz/src

# Use CMake (project provides CMakeLists)
RUN mkdir -p build && cd build && \
    cmake -G Ninja \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DROCKSDB_BUILD_SHARED=OFF \
      -DWITH_TESTS=OFF \
      -DWITH_BENCHMARK_TOOLS=OFF \
      -DWITH_TOOLS=OFF \
      -DWITH_GFLAGS=OFF \
      -DFAIL_ON_WARNINGS=OFF \
      .. && \
    ninja -v install
