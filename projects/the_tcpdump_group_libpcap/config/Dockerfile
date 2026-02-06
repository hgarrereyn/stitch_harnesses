ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build \
      pkg-config \
      flex bison \
      libnl-3-dev libnl-genl-3-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libpcap (static only)
WORKDIR /fuzz/src
RUN cmake -S . -B build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DDISABLE_DBUS=ON \
      -DDISABLE_RDMA=ON \
      -DDISABLE_DAG=ON \
      -DDISABLE_SNF=ON \
      -DDISABLE_BLUETOOTH=ON \
      -DDISABLE_NETMAP=ON \
    && cmake --build build -j \
    && cmake --install build
