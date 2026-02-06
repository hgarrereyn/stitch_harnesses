ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make \
    zlib1g-dev pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
RUN mkdir -p build && cd build && \
    cmake -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DMATIO_SHARED=OFF \
      -DMATIO_WITH_ZLIB=ON \
      -DMATIO_WITH_HDF5=OFF \
      -DMATIO_MAT73=OFF \
      .. && \
    ninja -j"$(nproc)" && ninja install
