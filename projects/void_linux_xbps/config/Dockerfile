ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies for libxbps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    zlib1g-dev \
    libarchive-dev \
    libssl-dev \
    liblz4-dev \
    libzstd-dev \
    libbz2-dev \
    liblzma-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure, build, and install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install && \
    make -j"$(nproc)" && \
    make install
