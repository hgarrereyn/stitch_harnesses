ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library; build via CMake to install headers into /fuzz/install
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure and install only the headers
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DPHMAP_INSTALL=ON \
    -DPHMAP_BUILD_TESTS=OFF \
    -DPHMAP_BUILD_EXAMPLES=OFF \
 && cmake --build build \
 && cmake --install build
