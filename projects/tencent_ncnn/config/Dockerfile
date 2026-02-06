ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools needed inside the container
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure and build static lib, install to /fuzz/install
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DNCNN_SHARED_LIB=OFF \
    -DNCNN_VULKAN=OFF \
    -DNCNN_OPENMP=OFF \
    -DNCNN_THREADS=ON \
    -DNCNN_BUILD_TOOLS=OFF \
    -DNCNN_BUILD_EXAMPLES=OFF \
    -DNCNN_BUILD_BENCHMARK=OFF \
    -DNCNN_INSTALL_SDK=ON \
 && cmake --build build --target install -- -v
