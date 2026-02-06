ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build Tracy as a static library, install to /fuzz/install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DTRACY_STATIC=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DTRACY_LTO=OFF \
 && cmake --build build --target install -- -v
