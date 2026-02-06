ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 \
    cmake \
    ninja-build \
    make \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build and install DuckDB
WORKDIR /fuzz/src

# Configure
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHELL=OFF \
    -DBUILD_UNITTESTS=OFF \
    -DBUILD_BENCHMARKS=OFF

# Build & Install
RUN cmake --build build --target install -j
