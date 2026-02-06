ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    make \
    ninja-build \
    libpcre2-dev \
    libxxhash-dev \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libyang as a static library
WORKDIR /fuzz/build
RUN cmake -S /fuzz/src -B . \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_TOOLS=OFF \
    -DENABLE_TESTS=OFF \
 && make -j"$(nproc)" \
 && make install
