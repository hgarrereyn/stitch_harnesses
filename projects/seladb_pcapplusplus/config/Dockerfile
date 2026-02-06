ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake \
      ninja-build \
      make \
      libpcap-dev \
      pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install PcapPlusPlus
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DPCAPPP_INSTALL=ON \
    -DPCAPPP_BUILD_TESTS=OFF \
    -DPCAPPP_BUILD_EXAMPLES=OFF \
    -DPCAPPP_BUILD_TUTORIALS=OFF \
    -DPCAPPP_BUILD_PCAPPP=ON \
    -DPCAPPP_USE_DPDK=OFF \
    -DPCAPPP_USE_PF_RING=OFF \
    -DPCAPPP_USE_XDP=OFF \
 && cmake --build /fuzz/build --target install -j$(nproc)
