ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    libdbus-1-dev \
    libboost-dev \
    libtool \
    autoconf \
    automake \
    autoconf-archive \
    make \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Bootstrap autotools, configure for static where possible, and install
RUN ./bootstrap.sh && \
    ./configure \
      --prefix=/fuzz/install \
      --disable-shared \
      --enable-static \
      --sysconfdir=/fuzz/install/etc \
    && \
    make -j"$(nproc)" && \
    make install
