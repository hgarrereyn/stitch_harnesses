ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and Abseil (use system absl for linking)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    git \
    ca-certificates \
    pkg-config \
    libabsl-dev \
    && rm -rf /var/lib/apt/lists/*

ENV INSTALL_PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Configure the project
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -DBUILD_SHARED_LIBS=OFF \
    -DOpenCensus_BUILD_TESTING=OFF

# Build and install
RUN cmake --build build --target install -- -v
