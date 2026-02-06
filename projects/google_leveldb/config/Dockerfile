ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building leveldb and optional compression libs
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    cmake \
    ninja-build \
    make \
    libsnappy-dev \
    libzstd-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install leveldb as a static library
WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_CXX_STANDARD=17 \
    -DCMAKE_CXX_STANDARD_REQUIRED=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DLEVELDB_BUILD_TESTS=OFF \
    -DLEVELDB_BUILD_BENCHMARKS=OFF \
 && cmake --build /fuzz/build --target install -j$(nproc)
