ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    make \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install glslang
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -S /fuzz/src \
    -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_OPT=OFF \
    -DBUILD_SHARED_LIBS=OFF \
    -DGLSLANG_ENABLE_INSTALL=ON \
 && cmake --build /fuzz/build --target install -j$(nproc)
