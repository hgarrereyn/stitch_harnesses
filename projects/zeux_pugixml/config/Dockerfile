ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    make \
    ninja-build \
    pkg-config \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install pugixml as a static library
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DPUGIXML_INSTALL=ON \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo
RUN cmake --build build --target install -j$(nproc)
