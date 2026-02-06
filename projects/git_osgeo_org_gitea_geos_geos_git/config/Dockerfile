ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools (cmake, ninja). Base image may be minimal.
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Configure, build, and install static libs
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF && \
    cmake --build /fuzz/build -j"$(nproc)" && \
    cmake --install /fuzz/build
