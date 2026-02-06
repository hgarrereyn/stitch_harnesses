ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for Open vSwitch (userspace libraries)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libssl-dev libcap-ng-dev libunwind-dev libunbound-dev zlib1g-dev \
    binutils-dev libiberty-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script and build
RUN ./boot.sh && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --prefix=/fuzz/install --enable-shared=no --enable-static=yes && \
    make -j"$(nproc)" && \
    make install
