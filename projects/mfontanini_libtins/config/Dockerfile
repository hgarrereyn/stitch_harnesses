ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake \
    ninja-build \
    libpcap-dev \
    libssl-dev \
    libboost-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libtins (static only)
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DLIBTINS_BUILD_SHARED=0 \
    -DLIBTINS_BUILD_TESTS=0 \
    -DLIBTINS_BUILD_EXAMPLES=0 \
    -DLIBTINS_ENABLE_CXX11=1

RUN cmake --build /fuzz/build --target install -j$(nproc)
