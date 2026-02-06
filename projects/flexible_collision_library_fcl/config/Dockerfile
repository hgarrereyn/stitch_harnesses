ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    libeigen3-dev \
    libccd-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install FCL
WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DFCL_WITH_OCTOMAP=OFF \
    -DFCL_STATIC_LIBRARY=ON \
    -DBUILD_TESTING=OFF
RUN cmake --build build --target install -j$(nproc)
