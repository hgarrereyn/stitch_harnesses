ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    cmake \
    ninja-build \
    rustc cargo \
    libssl-dev \
    zlib1g-dev \
    libbz2-dev \
    libpcre2-dev \
    libxml2-dev \
    libjson-c-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install libclamav (static preferred)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DENABLE_LIBCLAMAV_ONLY=ON \
    -DENABLE_APP=OFF \
    -DENABLE_EXAMPLES=OFF \
    -DENABLE_TESTS=OFF \
    -DENABLE_SYSTEMD=OFF \
    -DENABLE_SHARED_LIB=OFF \
    -DENABLE_STATIC_LIB=ON \
    && cmake --build /fuzz/build --target install --config RelWithDebInfo
