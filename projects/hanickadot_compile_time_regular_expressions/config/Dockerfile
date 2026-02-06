ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools required for configuring the header-only library
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build && \
    rm -rf /var/lib/apt/lists/*

# Configure and install headers and CMake package files
RUN cmake -G Ninja -S /fuzz/src -B /tmp/build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCTRE_BUILD_TESTS=OFF \
    -DCTRE_BUILD_PACKAGE=OFF \
    -DCTRE_MODULE=OFF && \
    cmake --build /tmp/build --target install
