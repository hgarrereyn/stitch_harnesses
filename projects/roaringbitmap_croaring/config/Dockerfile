ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and any extra dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    git cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install CRoaring as a static library
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DROARING_BUILD_STATIC=ON \
    -DENABLE_ROARING_TESTS=OFF \
    -DENABLE_ROARING_MICROBENCHMARKS=OFF \
    -DROARING_BUILD_LTO=OFF \
    -DROARING_USE_CPM=OFF && \
    cmake --build build --target install
