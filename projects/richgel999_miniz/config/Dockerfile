ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and build with CMake (static lib, no examples/tests)
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_TESTS=OFF \
    -DINSTALL_PROJECT=ON \
 && cmake --build build --target install -j
