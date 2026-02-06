ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    make \
    autoconf \
    ca-certificates \
    libavahi-client-dev \
    libdbus-1-dev \
    libssl-dev \
    zlib1g-dev \
    libpng-dev \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Configure, build, and install libcups statically into /fuzz/install
RUN ./configure \
      --prefix=/fuzz/install \
      --disable-shared \
      --with-tls=openssl \
      --with-dnssd=avahi \
    && make -j"$(nproc)" \
    && make install
