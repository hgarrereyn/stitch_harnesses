ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    autoconf \
    automake \
    libtool \
    pkg-config \
    flex \
    bison \
    libssl-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install YARA (static library preferred)
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./bootstrap.sh && \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static && \
    make -j"$(nproc)" && \
    make install
