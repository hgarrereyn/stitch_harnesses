ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Capstone (static library)
WORKDIR /fuzz/src

# Use out-of-tree build
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCAPSTONE_BUILD_SHARED_LIBS=OFF \
    -DCAPSTONE_BUILD_STATIC_LIBS=ON \
    -DCAPSTONE_BUILD_CSTOOL=OFF \
    -DCAPSTONE_BUILD_LEGACY_TESTS=OFF \
    -DCAPSTONE_BUILD_CSTEST=OFF \
    -DCAPSTONE_INSTALL=ON \
 && cmake --build build --target install
