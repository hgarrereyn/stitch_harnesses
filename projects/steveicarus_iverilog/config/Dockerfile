ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf \
    gperf \
    make \
    bison \
    flex \
    libreadline-dev \
    libncurses-dev \
    zlib1g-dev \
    libbz2-dev \
    pkg-config \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script (building from git) and configure with fuzzing compilers
RUN sh autoconf.sh && \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=/fuzz/install && \
    make -j"$(nproc)" && \
    make install
