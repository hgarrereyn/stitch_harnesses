ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools required (cmake, ninja)
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build oatpp as a static library
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/build

RUN cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DOATPP_BUILD_TESTS=OFF \
    -DOATPP_LINK_TEST_LIBRARY=OFF \
    /fuzz/src \
 && ninja -j$(nproc) \
 && ninja install
