ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake may not be present in base image) - jsoncons is header-only
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and install headers and CMake package files
RUN cmake -S . -B build \
    -G Ninja \
    -DJSONCONS_BUILD_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
 && cmake --build build \
 && cmake --install build
