ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf automake libtool pkg-config \
    flex bison \
    zlib1g-dev libpcre2-dev libssl-dev \
    make python3 wget \
    && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Bootstrap and configure
RUN ./autogen.sh && \
    ./configure --prefix=/fuzz/install --with-shared-libs=yes && \
    make -j$(nproc) && \
    make install

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:/fuzz/install/lib/dovecot/pkgconfig:$PKG_CONFIG_PATH
