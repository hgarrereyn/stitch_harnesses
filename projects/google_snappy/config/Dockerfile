ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure, build, and install Snappy as a static library
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DSNAPPY_BUILD_TESTS=OFF \
    -DSNAPPY_BUILD_BENCHMARKS=OFF \
    -DSNAPPY_INSTALL=ON \
 && cmake --build build --target install -j
