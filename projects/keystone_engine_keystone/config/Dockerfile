ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    python3 \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Keystone
WORKDIR /fuzz/src

# Out-of-source build
RUN mkdir -p build && cd build \
 && CC=gf_libafl_cc CXX=gf_libafl_cxx \
    cmake -G Ninja .. \
      -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
      -DBUILD_LIBS_ONLY=ON \
      -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
 && ninja -v \
 && ninja install
