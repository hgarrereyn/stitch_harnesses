ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library; build and install with CMake
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and install GSL
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DGSL_TEST=OFF \
    -DGSL_INSTALL=ON \
 && cmake --build build --target install
