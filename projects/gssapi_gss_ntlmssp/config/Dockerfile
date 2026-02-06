ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config make \
    libkrb5-dev libunistring-dev libssl-dev zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Autotools bootstrap, configure and install
RUN autoreconf -f -i && \
    ./configure \
      --prefix=/fuzz/install \
      --with-manpages=no \
      --disable-nls \
      --with-wbclient=no \
      CC="$CC" CXX="$CXX" && \
    make -j"$(nproc)" && \
    make install

# Ensure install prefix exists
RUN mkdir -p /fuzz/install
