ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf \
    autoconf-archive \
    automake \
    libtool \
    pkg-config \
    make \
    ninja-build \
    git \
    doxygen \
    libssl-dev \
    libjson-c-dev \
    libini-config-dev \
    libcurl4-openssl-dev \
    uuid-dev \
    libltdl-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build and install static libraries
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./bootstrap && \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static && \
    make -j"$(nproc)" && \
    make install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig
