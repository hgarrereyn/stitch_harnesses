ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and library dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libpng-dev \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libharu (static lib preferred)
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DLIBHPDF_EXAMPLES=OFF
RUN cmake --build build --target install
