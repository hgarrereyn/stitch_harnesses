ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Use clang wrappers provided by the fuzzing runtime
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DWITH_TOOLS=OFF \
    -DWITH_TESTS=OFF \
    -DWITHOUT_PNG=ON \
 && cmake --build build -j \
 && cmake --install build
