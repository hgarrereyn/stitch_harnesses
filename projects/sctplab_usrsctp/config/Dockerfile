ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build usrsctp as a static library, install into /fuzz/install
WORKDIR /fuzz/src
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -Dsctp_build_shared_lib=OFF \
 && cmake --build build --target install
