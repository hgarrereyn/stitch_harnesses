ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools needed for this project
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Build and install kissfft as a static library
WORKDIR /fuzz/src

# Configure with CMake: use fuzz compilers, static lib, disable tools/tests
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DKISSFFT_STATIC=ON \
    -DKISSFFT_TOOLS=OFF \
    -DKISSFFT_TEST=OFF \
    -DKISSFFT_PKGCONFIG=OFF

RUN cmake --build build --target install
