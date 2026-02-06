ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    ninja-build \
    cmake \
    make \
    git \
    curl \
    rustc \
    cargo \
    libssl-dev \
    zlib1g-dev \
    libbz2-dev \
    libpcre2-dev \
    libxml2-dev \
    libjson-c-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install static libclamav only
WORKDIR /fuzz

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DENABLE_SHARED_LIB=OFF \
    -DENABLE_STATIC_LIB=ON \
    -DENABLE_LIBCLAMAV_ONLY=ON \
    -DENABLE_APP=OFF \
    -DENABLE_EXAMPLES=OFF \
    -DENABLE_TESTS=OFF \
    -DENABLE_MAN_PAGES=OFF \
    -DENABLE_SYSTEMD=OFF \
    -DOPTIMIZE=OFF

# Build & install
RUN cmake --build /fuzz/build --target install --config RelWithDebInfo
