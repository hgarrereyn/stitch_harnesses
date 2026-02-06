ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools and dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install only static libraries
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build \
    -G "Ninja" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DACL_BUILD_SHARED=NO \
 && cmake --build /fuzz/build -j$(nproc) \
 && cmake --install /fuzz/build
