ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autotools and optional compression libs
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    zlib1g-dev libbz2-dev liblzma-dev libzstd-dev libseccomp-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script and build static libmagic
RUN autoreconf -fiv
RUN CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --prefix=/fuzz/install \
    --disable-shared --enable-static

RUN make -j"$(nproc)" && make install
