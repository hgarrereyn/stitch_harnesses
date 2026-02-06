ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libcbor as a static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz

# Configure with CMake and Ninja, install prefix /fuzz/install
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=OFF \
    -DWITH_TESTS=OFF -DWITH_EXAMPLES=OFF
# Build the library explicitly (install target doesn't depend on build here)
RUN cmake --build /fuzz/build --target cbor -j$(nproc)
# Install into /fuzz/install
RUN cmake --build /fuzz/build --target install -j$(nproc)
