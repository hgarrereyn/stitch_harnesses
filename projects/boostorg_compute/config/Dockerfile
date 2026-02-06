ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: OpenCL headers/runtime, Boost headers, and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ocl-icd-opencl-dev \
    libboost-dev \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and install the header-only library
WORKDIR /fuzz/src

# Use out-of-tree build
RUN mkdir -p build && cd build \
 && cmake -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    .. \
 && ninja install

# The headers are installed under /fuzz/install/include/compute
