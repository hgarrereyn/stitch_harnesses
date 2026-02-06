ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building libpng (zlib) and build tools (cmake, ninja)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    zlib1g-dev cmake ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Build and install libpng statically using CMake
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
WORKDIR /fuzz/src

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DPNG_STATIC=ON -DPNG_SHARED=OFF -DPNG_FRAMEWORK=OFF \
    -DPNG_TESTS=OFF -DPNG_TOOLS=OFF \
 && cmake --build build --target install
