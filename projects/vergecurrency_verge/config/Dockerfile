ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autoreconf-based build
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    automake autoconf libtool pkg-config \
    libssl-dev libevent-dev zlib1g-dev \
    libseccomp-dev libcap-dev \
    libboost-system-dev libboost-filesystem-dev libboost-thread-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Prepare build system without invoking upstream autogen.sh (tor submodule absent)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN autoreconf -fi && \
    (cd src/secp256k1 && ./autogen.sh)

# Build and install secp256k1 first so libvergeconsensus can link against it
RUN cd src/secp256k1 && \
    ./configure --prefix=/fuzz/install --disable-shared --enable-static --enable-module-recovery && \
    make -j"$(nproc)" && make install && cd /fuzz/src

# Configure, build and install minimal components with static libs only
RUN ./configure \
      --prefix=/fuzz/install \
      --disable-wallet \
      --without-gui \
      --disable-zmq \
      --without-miniupnpc \
      --disable-bench \
      --disable-tests \
      --with-libs \
      --without-utils \
      --without-daemon \
      --enable-static \
      --disable-shared && \
    make -j"$(nproc)" && \
    make install

