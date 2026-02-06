ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf automake libtool pkg-config libogg-dev build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:${PKG_CONFIG_PATH}

WORKDIR /fuzz/src

# Generate configure script and build
RUN ./autogen.sh && \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static CC=${CC} CXX=${CXX} && \
    make -j$(nproc) && \
    make install
