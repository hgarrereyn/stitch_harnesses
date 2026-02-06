ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies needed by the build
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    cmake \
    ninja-build \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

# Configure
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DJERRY_CMDLINE=OFF \
    -DJERRY_CMDLINE_TEST=OFF \
    -DJERRY_CMDLINE_SNAPSHOT=OFF \
    -DUNITTESTS=OFF \
    -DDOCTESTS=OFF \
    -DENABLE_LTO=OFF \
    -DJERRY_EXT=ON \
    -DJERRY_PORT=ON

# Build and install
RUN cmake --build /fuzz/build --target install -- -v
