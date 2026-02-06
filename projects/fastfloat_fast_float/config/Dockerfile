ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools in case base image lacks them
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake ninja-build make pkg-config ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Configure, build (interface target), and install headers to /fuzz/install
RUN cmake -S /fuzz/src -B /tmp/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DFASTFLOAT_INSTALL=ON \
 && cmake --build /tmp/build \
 && cmake --install /tmp/build \
 && rm -rf /tmp/build
