ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool make pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script from git and configure for static build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./autogen.sh && \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static --disable-docs && \
    make -j"$(nproc)" && \
    make install
