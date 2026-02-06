ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for optional features and build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    pkg-config \
    libssl-dev \
    libsasl2-dev \
    zlib1g-dev \
    libzstd-dev \
    libcurl4-openssl-dev \
    linux-libc-dev \
    && rm -rf /var/lib/apt/lists/*

# Build and install librdkafka
WORKDIR /fuzz/src
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install \
    && make -j$(nproc) \
    && make install DESTDIR= \
    && true

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:${PKG_CONFIG_PATH}
