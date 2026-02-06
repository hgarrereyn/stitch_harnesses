ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libeigen3-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install Ceres
WORKDIR /fuzz/src

# Build shared to simplify linking against Abseil
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_TESTING=OFF \
    -DBUILD_EXAMPLES=OFF \
    -DBUILD_BENCHMARKS=OFF \
    -DSUITESPARSE=OFF \
    -DLAPACK=OFF \
 && cmake --build build --target install
