ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    libboost-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install QuantLib (static)
WORKDIR /fuzz/src
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DQL_BUILD_EXAMPLES=OFF \
    -DQL_BUILD_TEST_SUITE=OFF \
 && cmake --build build --target install -j
