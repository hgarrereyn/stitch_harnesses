ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and image codec dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    pkg-config \
    zlib1g-dev \
    libpng-dev \
    libjpeg-turbo8-dev \
    libtiff-dev \
    libgif-dev \
    libwebp-dev \
    libopenjp2-7-dev \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install leptonica as static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_PROG=OFF \
    -DSYM_LINK=OFF
RUN cmake --build /fuzz/build --target install -j$(nproc)
