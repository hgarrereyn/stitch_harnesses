ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    pkg-config \
    ninja-build \
    cmake \
    libssl-dev \
    libcbor-dev \
    zlib1g-dev \
    libudev-dev \
    libpcsclite-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libfido2 as a static library
WORKDIR /fuzz/src

# Configure with CMake
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_TESTS=OFF \
    -DBUILD_TOOLS=OFF \
    -DBUILD_MANPAGES=OFF \
    -DUSE_HIDAPI=OFF

# Build and install
RUN cmake --build build --target install --config Release
