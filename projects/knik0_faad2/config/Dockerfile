ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install FAAD2 as a static library
WORKDIR /fuzz/src

# Create build directory
RUN mkdir -p build && cd build && \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    cmake -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DFAAD_BUILD_CLI=OFF \
      .. && \
    ninja -j$(nproc) && \
    ninja install
